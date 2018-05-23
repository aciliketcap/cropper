#ifndef RECTSELECTION_H
#define RECTSELECTION_H

#include <QRect>
#include <QSize>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QBrush>

#define RECT_SELECTION_DEFAULT_HANDLE_SIZE 5;

class RectSelection
{
public:
    RectSelection();
    void resize(const QSize &s);
    int getHandleSize() const { return handleSize; }
    void setHandleSize(const int size);
    QSize getMinSize() const { return minSize; }
    void setMinSize(QSize size);
    void draw(QPainter &painter);
private:
    QSize minSize;
    bool minSizeSetManually; //if false use handleSize*2 as min
    void setDefaultMinSize() {
        minSizeSetManually = false;
        minSize = QSize((handleSize+1)*2, (handleSize+1)*2);
    }
    int handleSize;
    QRect frame;
    QRect tl, tr, bl, br;
    void adjustHandles();
    QPen penBorder;
    QPen penHandle;
    QBrush brushHandle;
};

#endif // RECTSELECTION_H
