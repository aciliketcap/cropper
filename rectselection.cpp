#include "rectselection.h"

RectSelection::RectSelection() :
    penFrame(QPen(Qt::blue, 0, Qt::DashLine)),
    penHandle(QPen(Qt::green, 0)),
    brushHandle(QBrush(Qt::gray))
{
    handleSize = RECT_SELECTION_DEFAULT_HANDLE_SIZE;
    setDefaultMinSize();
    frame = QRect(QPoint(0,0), minSize);
    tl = QRect(frame.topLeft(), QSize(handleSize, handleSize));
    tr = QRect(frame.topRight() - QPoint(handleSize,0), QSize(handleSize, handleSize));
    br = QRect(frame.bottomRight() - QPoint(handleSize, handleSize), QSize(handleSize, handleSize));
    bl = QRect(frame.bottomLeft() - QPoint(0, handleSize), QSize(handleSize, handleSize));
}


void RectSelection::adjustHandlePos(){
    tl.moveTopLeft(frame.topLeft());
    tr.moveTopRight(frame.topRight());
    br.moveBottomRight(frame.bottomRight());
    bl.moveBottomLeft(frame.bottomLeft());
}

void RectSelection::adjustHandleSize()
{
    tl.setSize(QSize(handleSize, handleSize));
    tr.setSize(QSize(handleSize, handleSize));
    br.setSize(QSize(handleSize, handleSize));
    bl.setSize(QSize(handleSize, handleSize));
}

void RectSelection::resize(const QSize &s) {
    frame.setSize(
                QSize(
                    s.width() > minSize.width() ? s.width() : minSize.width(),
                    s.height() > minSize.height() ? s.height() : minSize.height()
                    ));
    adjustHandlePos();
}

void RectSelection::draw(QPainter &painter) {
    QPen tmpPen = painter.pen();
    QBrush tmpBrush = painter.brush();

    painter.setPen(penFrame);
    painter.setBrush(Qt::NoBrush);

    painter.drawRect(frame);

    painter.setPen(penHandle);
    painter.setBrush(brushHandle);
    painter.drawRect(tl);
    painter.drawRect(tr);
    painter.drawRect(br);
    painter.drawRect(bl);

    painter.setPen(tmpPen);
    painter.setBrush(tmpBrush);
}

//properties
int RectSelection::getHandleSize() const
{
    return handleSize;
}

void RectSelection::setHandleSize(const int size) {
    handleSize = size;
    if(!minSizeSetManually)
        setDefaultMinSize();
    adjustHandleSize();
    resize(frame.size());
}

QSize RectSelection::getMinSize() const
{
    return minSize;
}

void RectSelection::setMinSize(const QSize &size) {
    if(size.width() <= 0 && size.height() <= 0)
        setDefaultMinSize();
    else
        minSize = size;
}

QBrush RectSelection::getBrushHandle() const
{
    return brushHandle;
}

void RectSelection::setBrushHandle(const QBrush &value)
{
    brushHandle = value;
}

QPen RectSelection::getPenHandle() const
{
    return penHandle;
}

void RectSelection::setPenHandle(const QPen &value)
{
    penHandle = value;
}

QPen RectSelection::getPenFrame() const
{
    return penFrame;
}

void RectSelection::setPenFrame(const QPen &value)
{
    penFrame = value;
}
