#include "rectselection.h"

RectSelection::RectSelection() :
    penFrame(QPen(Qt::blue, 0, Qt::DashLine)),
    penHandle(QPen(Qt::green, 0)),
    brushHandle(QBrush(Qt::gray)),
    lastPressedPos(QPoint(0,0))
{
    handleSize = RECT_SELECTION_DEFAULT_HANDLE_SIZE;
    setDefaultMinSize();
    frame = QRect(QPoint(handleSize, handleSize), minSize);
    tl = QRect(frame.topLeft() + QPoint(-handleSize, -handleSize), QSize(handleSize, handleSize));
    tr = QRect(frame.topRight() + QPoint(0, -handleSize), QSize(handleSize, handleSize));
    br = QRect(frame.bottomRight() + QPoint(-handleSize, 0), QSize(handleSize, handleSize));
    bl = QRect(frame.bottomLeft() + QPoint(0, 0), QSize(handleSize, handleSize));
}

void RectSelection::adjustHandlePos(){
    tl.moveBottomRight(frame.topLeft()+QPoint(-1,-1));
    tr.moveBottomLeft(frame.topRight()+QPoint(1,-1));
    br.moveTopLeft(frame.bottomRight()+QPoint(1,1));
    bl.moveTopRight(frame.bottomLeft()+QPoint(-1,1));
}

void RectSelection::adjustHandleSize()
{
    tl.setSize(QSize(handleSize, handleSize));
    tr.setSize(QSize(handleSize, handleSize));
    br.setSize(QSize(handleSize, handleSize));
    bl.setSize(QSize(handleSize, handleSize));
}

//move the rect to top left and set minimal size
void RectSelection::reinit()
{
    frame.setTopLeft(QPoint(handleSize, handleSize));
    frame.setSize(minSize);
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
    if(tl.contains(pos)) curPressed = Pressed::tl;
    else if(tr.contains(pos)) curPressed = Pressed::tr;
    else if(br.contains(pos)) curPressed = Pressed::br;
    else if(bl.contains(pos)) curPressed = Pressed::bl;
    else if(frame.contains(pos)) curPressed = Pressed::frame;
    else return;

    lastPressedPos = pos;
}

void RectSelection::checkCanvasBounds(QRect &newRect) {
    if(newRect.left() < 0)
        newRect.moveLeft(0);
    if(newRect.right() > canvasSize.width() - 1)
        newRect.moveRight(canvasSize.width() - 1);
    if(newRect.top() < 0)
        newRect.moveTop(0);
    if(newRect.bottom() > canvasSize.height() -1)
        newRect.moveBottom(canvasSize.height() - 1);
}

void RectSelection::checkSrcImgBounds(QRect &newRect) {
    if(newRect.left() < handleSize)
        newRect.moveLeft(handleSize);
    if(newRect.right() > canvasSize.width() - handleSize - 1)
        newRect.moveRight(canvasSize.width() - handleSize - 1);
    if(newRect.top() < handleSize)
        newRect.moveTop(handleSize);
    if(newRect.bottom() > canvasSize.height() - handleSize - 1)
        newRect.moveBottom(canvasSize.height() - handleSize - 1);
}

void RectSelection::moved(const QPoint &pos)
{
    if(curPressed == Pressed::none) return;

    QPoint delta = pos - lastPressedPos;
    lastPressedPos = pos;
    QRect newRect;
    //TODO: max size checks will be added below
    switch (curPressed) {
    case Pressed::tl:
        newRect = tl.translated(delta);
        checkCanvasBounds(newRect);
        if(frame.right() - newRect.right() < minSize.width())
            newRect.moveRight(frame.right() - minSize.width());
        if(frame.bottom() - newRect.bottom() < minSize.height())
            newRect.moveBottom(frame.bottom() - minSize.height());
        tl = newRect;
        frame.setTopLeft(tl.bottomRight()+QPoint(1,1));
        tr.moveBottomLeft(frame.topRight()+QPoint(1,-1));
        bl.moveTopRight(frame.bottomLeft()+QPoint(-1,1));
        break;
    case Pressed::tr:
        newRect = tr.translated(delta);
        checkCanvasBounds(newRect);
        if(newRect.left() - frame.left() < minSize.width())
            newRect.moveLeft(frame.left() + minSize.width());
        if(frame.bottom() - newRect.bottom() < minSize.height())
            newRect.moveBottom(frame.bottom() - minSize.height());
        tr = newRect;
        frame.setTopRight(tr.bottomLeft()+QPoint(-1,1));
        tl.moveBottomRight(frame.topLeft()+QPoint(-1,-1));
        br.moveTopLeft(frame.bottomRight()+QPoint(1,1));
        break;
    case Pressed::br:
        newRect = br.translated(delta);
        checkCanvasBounds(newRect);
        if(newRect.left() - frame.left() < minSize.width())
            newRect.moveLeft(frame.left() + minSize.width());
        if(newRect.top() - frame.top() < minSize.width())
            newRect.moveTop(frame.top() + minSize.height());
        br = newRect;
        frame.setBottomRight(br.topLeft()+QPoint(-1,-1));
        tr.moveBottomLeft(frame.topRight()+QPoint(1,-1));
        bl.moveTopRight(frame.bottomLeft()+QPoint(-1,1));
    break;
    case Pressed::bl:
        newRect = bl.translated(delta);
        checkCanvasBounds(newRect);
        if(frame.right() - newRect.right() < minSize.width())
            newRect.moveRight(frame.right() - minSize.width());
        if(newRect.top() - frame.top() < minSize.width())
            newRect.moveTop(frame.top() + minSize.height());
        bl = newRect;
        frame.setBottomLeft(bl.topRight()+QPoint(1,-1));
        tl.moveBottomRight(frame.topLeft()+QPoint(-1,-1));
        br.moveTopLeft(frame.bottomRight()+QPoint(1,1));
        break;
    case Pressed::frame:
        newRect = frame.translated(delta);
        checkSrcImgBounds(newRect);
        frame = newRect;
        adjustHandlePos();
        break;
    default:
        break;
    }
}

//TODO: release pressed when mouse is moved outside the widget too!
void RectSelection::released(const QPoint& /* pos */)
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
    reinit();
}

void RectSelection::setDefaultMinSize() {
    minSizeSetManually = false;
    minSize = QSize(1,1);
}

void RectSelection::setCanvasSize(const QSize &value)
{
    canvasSize = value;
}

QRect RectSelection::getFrame() const
{
    //return the coordinates relative to the top left of the rectangle containing the image
    QRect frameOnImage = frame;
    frameOnImage.moveTopLeft(frame.topLeft() - QPoint(handleSize, handleSize));
    return frameOnImage;
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
