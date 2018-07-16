#include "cropcanvas.h"
#include <QtWidgets>

//TODO: use const values instead of macro defs for defaults
#define CROP_CANVAS_DEFAULT_ZOOM_AMOUNT 1.0

CropCanvas::CropCanvas(QWidget *parent) :
    QWidget(parent),
    cropArea(RectSelection()),
    brushSrcImgFrame(Qt::BrushStyle::Dense4Pattern),
    padding(0),
    canvasSize(0,0),
    zoomAmount(CROP_CANVAS_DEFAULT_ZOOM_AMOUNT)
{
    //TODO: use transformations instead of keeping points and ratios
}

CropCanvas::~CropCanvas()
{
}

void CropCanvas::loadImage(QImage srcImg)
{
    int handleSize = cropArea.getHandleSize();
    this->srcImg = srcImg;
    this->padding = handleSize;
    this->canvasSize = QSize(
                srcImg.width() + handleSize * 2,
                srcImg.height() + handleSize * 2);
    this->setMinimumSize(canvasSize);

    this->paddingRects[0] = QRect(0, 0, canvasSize.width(), padding);
    this->paddingRects[1] = QRect(0, padding, padding, srcImg.height());
    this->paddingRects[2] = QRect(canvasSize.width() - padding, padding, padding, srcImg.height());
    this->paddingRects[3] = QRect(0, canvasSize.height() - padding, canvasSize.width(), padding);

    update();

    cropArea.setCanvasSize(canvasSize);
    cropArea.reinit();
    if(!croppedImg.isNull())
        croppedImg = QImage();
    if(!croppedImgPixmap.isNull())
        croppedImgPixmap = QPixmap();
    emit cropCleared();
}

//events
void CropCanvas::paintEvent(QPaintEvent * /* event */)
{
    if(!this->srcImg.isNull()) {
        //paint whole widget, not just dirty portion
        //TODO: only render necessary region later

        QPainter painter(this);
        QBrush tmpBrush = painter.brush();

        painter.fillRect(paddingRects[0], brushSrcImgFrame);
        painter.fillRect(paddingRects[1], brushSrcImgFrame);
        painter.fillRect(paddingRects[2], brushSrcImgFrame);
        painter.fillRect(paddingRects[3], brushSrcImgFrame);

        //painter.scale(zoomAmount, zoomAmount);
        painter.drawImage(padding + 1, padding + 1, srcImg);
        //painter.scale(1/zoomAmount, 1/zoomAmount);

        cropArea.draw(painter);
        painter.setBrush(tmpBrush);
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

QBrush CropCanvas::getBrushSrcImgFrame() const
{
    return brushSrcImgFrame;
}

void CropCanvas::setBrushSrcImgFrame(const QBrush &value)
{
    brushSrcImgFrame = value;
}

CropCanvas::ImageCroppedOutput CropCanvas::getCropOutput() const
{
    return cropOutput;
}

void CropCanvas::setCropOutput(const ImageCroppedOutput &value)
{
    cropOutput = value;
}

QImage CropCanvas::getCroppedImg() const
{
    return croppedImg;
}

QPixmap CropCanvas::getCroppedImgPixmap()
{
    if(!croppedImg.isNull() && croppedImgPixmap.isNull())
        croppedImgPixmap = QPixmap::fromImage(croppedImg);
    return croppedImgPixmap;
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
    if(srcImg.isNull()) return;

    QRect translatedRect = cropArea.getFrame();
    //TODO: do these using transformations
    //translatedRect.moveTopLeft((translatedRect.topLeft() - (srcImgPos*zoomAmount)) * 1/zoomAmount);
    //translatedRect.setBottomRight(translatedRect.bottomRight() * 1/zoomAmount);

    croppedImg = srcImg.copy(translatedRect);

    if(!croppedImgPixmap.isNull())
        croppedImgPixmap = QPixmap();

    switch (cropOutput) {
    case ImageCroppedOutput::qImage:
        //do not produce a QPixmap until asked
        emit imageCropped(croppedImg);
        break;
    case ImageCroppedOutput::qPixmap:
        croppedImgPixmap = QPixmap::fromImage(croppedImg);
        emit imageCropped(croppedImgPixmap);
        break;
    case ImageCroppedOutput::both:
        croppedImgPixmap = QPixmap::fromImage(croppedImg);
        emit imageCropped(croppedImgPixmap);
        emit imageCropped(croppedImg);
        break;
    default:
        break;
    }
}
