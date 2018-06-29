#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
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
    CropCanvas *cropCanvas;
    QFileDialog *prepareImageFileDialog(bool isSaveDialog, const QString &dialogTitle);

private slots:
    void openSourceFile();
    void saveCroppedImage();
};

#endif // MAINWINDOW_H
