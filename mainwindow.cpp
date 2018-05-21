#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImageReader>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QImageReader r("../photo/sample.jpg");
    const QImage sampleImg = r.read();
    if(sampleImg.isNull()) {
        QMessageBox::information(this,
                                 QGuiApplication::applicationDisplayName(),
                                 tr("load failed: %1").arg(r.errorString()));
    } else {
        ui->srcImg->setPixmap(QPixmap::fromImage(sampleImg));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
