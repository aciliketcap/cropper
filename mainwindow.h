#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

public slots:
    //TODO: rename and move this to private slots
    void cropHandler();

private:
    Ui::MainWindow *ui;
    CropCanvas *cropCanvas;

private slots:
    void openSourceFile();
};

#endif // MAINWINDOW_H
