#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImageReader>
#include <QMessageBox>
#include <QLayout>
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageWriter>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scrollArea(new QScrollArea),
    cropCanvas(new CropCanvas)
{
    ui->setupUi(this);

    ui->btnCrop->setEnabled(false);
    //TODO: do these from UI form file after making CropCanvas a custom widget
    //configure cropCanvas (hardcoded)
    cropCanvas->setCropOutput(CropCanvas::ImageCroppedOutput::qPixmap);
    cropCanvas->setCropAreaHandleSize(20);
    scrollArea->setWidget(cropCanvas);
    ui->verticalLayout_2->addWidget(scrollArea);

    //TODO: do these using transformations
    //cropCanvas->setZoomAmount(2.0);
    //cropCanvas->setSrcImgPos(QPoint(40,40));

    //connect signals inside the code (hardcoded)
    connect(ui->btnCrop, &QPushButton::clicked, cropCanvas, &CropCanvas::crop);
    //connect(cropCanvas, static_cast<void(CropCanvas::*)(QPixmap)>(&CropCanvas::imageCropped), ui->lblCroppedImg, &QLabel::setPixmap);
    connect(cropCanvas, static_cast<void(CropCanvas::*)(QPixmap)>(&CropCanvas::imageCropped), this, &MainWindow::setCroppedImage);
    connect(cropCanvas, &CropCanvas::cropCleared, ui->lblCroppedImg, &QLabel::clear);
}

MainWindow::~MainWindow()
{
    delete cropCanvas;
    delete ui;
}

QFileDialog *MainWindow::prepareImageFileDialog(bool isSaveDialog, const QString &dialogTitle) {
    auto dialog = new QFileDialog(this, dialogTitle);
    //try to open default Pictures dir
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    dialog->setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = isSaveDialog ? QImageWriter::supportedMimeTypes() : QImageReader::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog->setMimeTypeFilters(mimeTypeFilters);

    if(isSaveDialog) {
        dialog->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
        dialog->selectMimeTypeFilter("image/png");
        dialog->setFileMode(QFileDialog::AnyFile);
    } else {
        dialog->selectMimeTypeFilter("image/jpeg");
        dialog->setFileMode(QFileDialog::ExistingFile);
    }

    return dialog;
}

void MainWindow::adjustLblCroppedImageSize(QSize imageSize, QSize areaSize)
{
    if(imageSize.width() > areaSize.width()
            || imageSize.height() > areaSize.height()) {
        double imgRatio = imageSize.width() / (double) imageSize.height();
        double areaRatio = areaSize.width() / (double) areaSize.height();

        if(imgRatio < areaRatio) {
            ui->lblCroppedImg->setMaximumHeight(areaSize.height());
            ui->lblCroppedImg->setMaximumWidth(areaSize.height() * imgRatio);
        } else {
            ui->lblCroppedImg->setMaximumWidth(areaSize.width());
            ui->lblCroppedImg->setMaximumHeight(areaSize.width() / imgRatio);
        }
        ui->lblCroppedImg->setScaledContents(true);
    } else {
        //set label size to minimum and disable scaling
        ui->lblCroppedImg->setMaximumSize(imageSize);
        ui->lblCroppedImg->setScaledContents(false);
    }
}

void MainWindow::openSourceImage()
{
    auto dialog = prepareImageFileDialog(false, tr("Open Source File"));

    if(dialog->exec()) {
        QImage tmpImg;
        if(!tmpImg.load(dialog->selectedFiles().first()))
            QMessageBox::information(
                        this,
                        QGuiApplication::applicationDisplayName(),
                        tr("Load failed"));
        else {
            ui->btnCrop->setEnabled(true);
            cropCanvas->loadImage(tmpImg);
        }
    }

    delete dialog;
}

void MainWindow::saveCroppedImage()
{
    QImage lastCroppedImage = cropCanvas->getCroppedImg();
    if(lastCroppedImage.isNull()) {
        QMessageBox::information(
                    this,
                    QGuiApplication::applicationDisplayName(),
                    tr("No image has been cropped"));
        return;
    }

    auto dialog = prepareImageFileDialog(true, tr("Save Cropped Image"));

    if(dialog->exec()) {
        if(!lastCroppedImage.save(dialog->selectedFiles().first())) {
            QMessageBox::information(
                        this,
                        QGuiApplication::applicationDisplayName(),
                        tr("Save failed")); //no way to get error info?
        }
    }

    delete dialog;
}

//we need to adjust the size of the image label too
void MainWindow::setCroppedImage(QPixmap croppedImgPixmap)
{
    adjustLblCroppedImageSize(croppedImgPixmap.size(), ui->verticalLayout_3->contentsRect().size());
    ui->lblCroppedImg->setPixmap(croppedImgPixmap);
    return;
}
