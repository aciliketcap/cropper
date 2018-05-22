#include "cropcanvas.h"
#include <QtWidgets>

CropCanvas::CropCanvas(QWidget *parent) : QWidget(parent)
{
    srcImg = NULL;
}

void CropCanvas::loadImage(const QImage *srcImg)
{
    this->srcImg = srcImg;
}

void CropCanvas::paintEvent(QPaintEvent *event)
{
    if(this->srcImg) {
        QPainter painter(this);
        QRect dirtyRect = event->rect();
        painter.drawImage(dirtyRect, *(this->srcImg), dirtyRect);
    }
}
