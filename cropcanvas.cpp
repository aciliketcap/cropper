#include "cropcanvas.h"
#include <QtWidgets>

#define CROP_CANVAS_DEFAULT_ZOOM_AMOUNT 1.0

CropCanvas::CropCanvas(QWidget *parent) :
    QWidget(parent),
    cropArea(RectSelection())
{
    srcImg = nullptr;
    zoomAmount = CROP_CANVAS_DEFAULT_ZOOM_AMOUNT;
}

void CropCanvas::loadImage(QImage *srcImg)
{
    this->srcImg = srcImg;
}

void CropCanvas::setZoomAmount(qreal newZoomAmount) {
    if(newZoomAmount <= 0)
        zoomAmount = CROP_CANVAS_DEFAULT_ZOOM_AMOUNT;
    else
        zoomAmount = newZoomAmount;
}


void CropCanvas::paintEvent(QPaintEvent *event)
{
    if(this->srcImg) {
        QPainter painter(this);

        //paint whole widget, not just dirty portion
        painter.scale(zoomAmount, zoomAmount);
        painter.drawImage(0, 0, *srcImg);
        painter.scale(1/zoomAmount, 1/zoomAmount);

        cropArea.draw(painter);
    }
}

void CropCanvas::mousePressEvent(QMouseEvent *event) {

}

void CropCanvas::mouseMoveEvent(QMouseEvent *event) {

}

void CropCanvas::mouseReleaseEvent(QMouseEvent *event) {

}
