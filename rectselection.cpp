#include "rectselection.h"

RectSelection::RectSelection() :
    penFrame(QPen(Qt::blue, 0, Qt::DashLine)),
    penHandle(QPen(Qt::green, 0)),
    brushHandle(QBrush(Qt::gray)),
    lastPressedPos(QPoint(0,0))
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

void RectSelection::pressed(const QPoint &pos)
{
    if(frame.contains(pos)){
        lastPressedPos = pos;
        if(tl.contains(pos)) curPressed = Pressed::tl;
        else if(tr.contains(pos)) curPressed = Pressed::tr;
        else if(br.contains(pos)) curPressed = Pressed::br;
        else if(bl.contains(pos)) curPressed = Pressed::bl;
        else curPressed = Pressed::frame;
    }
}

void RectSelection::moved(const QPoint &pos)
{
    if(curPressed == Pressed::none) return;

    QPoint delta = pos - lastPressedPos;
    lastPressedPos = pos;
    QRect newRect;
    switch (curPressed) {
    case Pressed::tl:
        newRect = tl.translated(delta);
        if(frame.right() - newRect.left() < minSize.width())
            newRect.moveLeft(frame.right() - minSize.width() + 1);
        if(frame.bottom() - newRect.top() < minSize.height())
            newRect.moveTop(frame.bottom() - minSize.height() + 1);
        tl = newRect;
        frame.setTopLeft(tl.topLeft());
        tr.moveTopRight(frame.topRight());
        bl.moveBottomLeft(frame.bottomLeft());
        break;
    case Pressed::tr:
        newRect = tr.translated(delta);
        if(newRect.right() - frame.left() < minSize.width())
            newRect.moveRight(frame.left() + minSize.width() - 1);
        if(frame.bottom() - newRect.top() < minSize.height())
            newRect.moveTop(frame.bottom() - minSize.height() + 1);
        tr = newRect;
        frame.setTopRight(tr.topRight());
        tl.moveTopLeft(frame.topLeft());
        br.moveBottomRight(frame.bottomRight());
        break;
    case Pressed::br:
        newRect = br.translated(delta);
        if(newRect.right() - frame.left() < minSize.width())
            newRect.moveRight(frame.left() + minSize.width() - 1);
        if(newRect.bottom() - frame.top() < minSize.width())
            newRect.moveBottom(frame.top() + minSize.height() - 1);
        br = newRect;
        frame.setBottomRight(br.bottomRight());
        tr.moveTopRight(frame.topRight());
        bl.moveBottomLeft(frame.bottomLeft());
    break;
    case Pressed::bl:
        newRect = bl.translated(delta);
        if(frame.right() - newRect.left() < minSize.width())
            newRect.moveLeft(frame.right() - minSize.width() + 1);
        if(newRect.bottom() - frame.top() < minSize.width())
            newRect.moveBottom(frame.top() + minSize.height() - 1);
        bl = newRect;
        frame.setBottomLeft(bl.bottomLeft());
        tl.moveTopLeft(frame.topLeft());
        br.moveBottomRight(frame.bottomRight());
        break;
    case Pressed::frame:
        frame.translate(delta);
        adjustHandlePos();
    break;
    default:
        break;
    }
}

//TODO: release pressed when moune is moved outside the widget too!
void RectSelection::released(const QPoint &pos)
{
    curPressed = Pressed::none;
    lastPressedPos = QPoint(0,0);
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

void RectSelection::setDefaultMinSize() {
    minSizeSetManually = false;
    minSize = QSize((handleSize+1)*2, (handleSize+1)*2);
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
