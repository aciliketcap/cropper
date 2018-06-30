#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImageReader>
#include <QMessageBox>
#include <QLayout>
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageWriter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cropCanvas(new CropCanvas)
{
    ui->setupUi(this);

    //TODO: do these from UI form file after making CropCanvas a custom widget
    ui->verticalLayout_2->addWidget(cropCanvas);
    //configure cropCanvas (hardcoded)
    cropCanvas->setCropOutput(CropCanvas::ImageCroppedOutput::qPixmap);
    cropCanvas->setCropAreaHandleSize(20);

    //TODO: do these using transformations
    //cropCanvas->setZoomAmount(2.0);
    //cropCanvas->setSrcImgPos(QPoint(40,40));

    //connect signals inside the code (hardcoded)
    connect(ui->btnCrop, &QPushButton::clicked, cropCanvas, &CropCanvas::crop);
    connect(cropCanvas, static_cast<void(CropCanvas::*)(QPixmap)>(&CropCanvas::imageCropped), ui->lblCroppedImg, &QLabel::setPixmap);
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

void MainWindow::openSourceImage()
{
    auto dialog = prepareImageFileDialog(false, tr("Open Source File"));

    if(dialog->exec()) {
        QImageReader r(dialog->selectedFiles().first());
        QImage *sampleImg = new QImage();
        if(!r.read(sampleImg)) {
            QMessageBox::information(
                        this,
                        QGuiApplication::applicationDisplayName(),
                        tr("load failed: %1").arg(r.errorString()));
        } else {
            cropCanvas->loadImage(sampleImg);
        }
    }

    delete dialog;
}

void MainWindow::saveCroppedImage()
{
    QImage* lastCroppedImage = cropCanvas->getCroppedImg();
    if(!lastCroppedImage) {
        QMessageBox::information(
                    this,
                    QGuiApplication::applicationDisplayName(),
                    tr("No image has been cropped"));
        return;
    }

    auto dialog = prepareImageFileDialog(true, tr("Save Cropped Image"));

    if(dialog->exec()) {
        if(!lastCroppedImage->save(dialog->selectedFiles().first())) {
            QMessageBox::information(
                        this,
                        QGuiApplication::applicationDisplayName(),
                        tr("save failed")); //no way to get error info?
        }
    }

    delete dialog;
}

