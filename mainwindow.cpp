#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImageReader>
#include <QMessageBox>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cropCanvas(new CropCanvas)
{
    ui->setupUi(this);
    ui->verticalLayout_2->addWidget(cropCanvas);

    cropCanvas->setZoomAmount(2.0);
    cropCanvas->setCropAreaHandleSize(20);

    QImageReader r("../photo/sample.jpg");
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

MainWindow::~MainWindow()
{
    delete cropCanvas;
    delete ui;
}
