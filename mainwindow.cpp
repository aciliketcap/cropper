#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImageReader>
#include <QMessageBox>
#include <QLayout>
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cropCanvas(new CropCanvas)
{
    ui->setupUi(this);
    ui->verticalLayout_2->addWidget(cropCanvas);
    connect(ui->btnCrop, SIGNAL(clicked()), this, SLOT(cropHandler()));

    //TODO: do these using transformations
    //cropCanvas->setZoomAmount(2.0);
    //cropCanvas->setSrcImgPos(QPoint(40,40));
    cropCanvas->setCropAreaHandleSize(20);
}

MainWindow::~MainWindow()
{
    delete cropCanvas;
    delete ui;
}

void MainWindow::cropHandler()
{
    cropCanvas->crop();
    ui->lblCroppedImg->setPixmap(QPixmap::fromImage(*cropCanvas->getCroppedImg()));
}

void MainWindow::openSourceFile()
{
    QFileDialog dialog(this, tr("Open Source File"));
    //try to open default Pictures dir
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = QImageReader::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    dialog.setFileMode(QFileDialog::ExistingFile);

    if(dialog.exec()) {
        QImageReader r(dialog.selectedFiles().first());
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
}
