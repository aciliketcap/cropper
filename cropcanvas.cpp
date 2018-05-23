#include "cropcanvas.h"
#include <QtWidgets>

CropCanvas::CropCanvas(QWidget *parent) :
    QWidget(parent),
    cropArea(RectSelection())
{
    srcImg = nullptr;
}

void CropCanvas::loadImage(QImage *srcImg)
{
    this->srcImg = srcImg;
}

void CropCanvas::paintEvent(QPaintEvent *event)
{
    if(this->srcImg) {
        QPainter painter(this);

        //paint whole widget, not just dirty portion
        painter.drawImage(0, 0, *srcImg);
        painter.scale(2.0, 2.0);

        cropArea.draw(painter);
    }
}

void CropCanvas::mousePressEvent(QMouseEvent *event) {

}

void CropCanvas::mouseMoveEvent(QMouseEvent *event) {

}

void CropCanvas::mouseReleaseEvent(QMouseEvent *event) {

}
