#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QScrollArea>
#include "cropcanvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QScrollArea *scrollArea;
    CropCanvas *cropCanvas;
    QFileDialog *prepareImageFileDialog(bool isSaveDialog, const QString &dialogTitle);

private slots:
    void openSourceImage();
    void saveCroppedImage();
};

#endif // MAINWINDOW_H
