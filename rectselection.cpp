#include "rectselection.h"

RectSelection::RectSelection() :
    penBorder(QPen(Qt::blue, 0, Qt::DashLine)),
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

void RectSelection::setHandleSize(const int size) {
    handleSize = size;
    if(!minSizeSetManually)
        setDefaultMinSize();
}

void RectSelection::setMinSize(QSize size) {
    if(size.width() <= 0 && size.height() <= 0)
        setDefaultMinSize();
    else
        minSize = size;
}

void RectSelection::adjustHandles(){
    tl.moveTopLeft(frame.topLeft());
    tr.moveTopRight(frame.topRight());
    br.moveBottomRight(frame.bottomRight());
    bl.moveBottomLeft(frame.bottomLeft());
}

void RectSelection::resize(const QSize &s) {
    frame.setSize(
                QSize(
                    s.width() > minSize.width() ? s.width() : minSize.width(),
                    s.height() > minSize.height() ? s.height() : minSize.height()
                    ));
    adjustHandles();
}

void RectSelection::draw(QPainter &painter) {
    QPen tmpPen = painter.pen();
    QBrush tmpBrush = painter.brush();

    painter.setPen(penBorder);
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


