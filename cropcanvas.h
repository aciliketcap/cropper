#ifndef CROPCANVAS_H
#define CROPCANVAS_H

#include <QWidget>
#include "rectselection.h"

class CropCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit CropCanvas(QWidget *parent = nullptr);
    void loadImage(QImage *srcImg);
    QImage* srcImg;
    RectSelection cropArea;
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:

};

#endif // CROPCANVAS_H
