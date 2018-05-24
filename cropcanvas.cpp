#include "cropcanvas.h"
#include <QtWidgets>

//TODO: use const values instead of macro defs for defaults
#define CROP_CANVAS_DEFAULT_ZOOM_AMOUNT 1.0

CropCanvas::CropCanvas(QWidget *parent) :
    QWidget(parent),
    cropArea(RectSelection())
{
    srcImg = nullptr;
    croppedImg = nullptr;
    //TODO: use transformations instead of keeping points and ratios
    srcImgPos = QPoint(0,0);
    zoomAmount = CROP_CANVAS_DEFAULT_ZOOM_AMOUNT;
}

CropCanvas::~CropCanvas()
{
    if(srcImg) delete srcImg;
    if(croppedImg) delete croppedImg;
}

void CropCanvas::loadImage(QImage *srcImg)
{
    this->srcImg = srcImg;
}

//events
void CropCanvas::paintEvent(QPaintEvent *event)
{
    if(this->srcImg) {
        QPainter painter(this);

        //paint whole widget, not just dirty portion
        painter.scale(zoomAmount, zoomAmount);
        painter.drawImage(srcImgPos, *srcImg);
        painter.scale(1/zoomAmount, 1/zoomAmount);

        cropArea.draw(painter);
    }
}

void CropCanvas::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        cropArea.pressed(event->pos());
    }
}

void CropCanvas::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        cropArea.moved(event->pos());
    }
    update();
}


void CropCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        cropArea.released(event->pos());
    }
}

QPoint CropCanvas::getSrcImgPos() const
{
    return srcImgPos;
}

void CropCanvas::setSrcImgPos(const QPoint &value)
{
    srcImgPos = value;
}

QImage *CropCanvas::getCroppedImg() const
{
    return croppedImg;
}

//properties - widget should be redrawn after setting visual properties!
qreal CropCanvas::getZoomAmount() const
{
    return zoomAmount;
}

void CropCanvas::setZoomAmount(qreal newZoomAmount) {
    if(newZoomAmount <= 0)
        zoomAmount = CROP_CANVAS_DEFAULT_ZOOM_AMOUNT;
    else
        zoomAmount = newZoomAmount;
}

int CropCanvas::getCropAreaHandleSize() const
{
    return cropArea.getHandleSize();
}

void CropCanvas::setCropAreaHandleSize(int size)
{
    cropArea.setHandleSize(size);
}

QSize CropCanvas::getCropAreaMinSize() const
{
    return cropArea.getMinSize();
}

void CropCanvas::setCropAreaMinSize(QSize size)
{
    cropArea.setMinSize(size);
}

QPen CropCanvas::getCropAreaPenFrame() const
{
    return cropArea.getPenFrame();
}

void CropCanvas::setCropAreaPenFrame(const QPen &value)
{
    cropArea.setPenFrame(value);
}

QPen CropCanvas::getCropAreaPenHandle() const
{
    return cropArea.getPenHandle();
}

void CropCanvas::setCropAreaPenHandle(const QPen &value)
{
    cropArea.setPenHandle(value);
}

QBrush CropCanvas::getCropAreaBrushHandle() const
{
    return cropArea.getBrushHandle();
}

void CropCanvas::setCropAreaBrushHandle(const QBrush &value)
{
    cropArea.setBrushHandle(value);
}

void CropCanvas::crop()
{
    QRect translatedRect = cropArea.getFrame();
    //TODO: do these using transformations
    //translatedRect.moveTopLeft((translatedRect.topLeft() - (srcImgPos*zoomAmount)) * 1/zoomAmount);
    //translatedRect.setBottomRight(translatedRect.bottomRight() * 1/zoomAmount);
    if(croppedImg) delete croppedImg;
    croppedImg = new QImage(srcImg->copy(translatedRect));

}
