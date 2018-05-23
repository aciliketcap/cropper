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
    void draw(QPainter &painter);
    //properties
    int getHandleSize() const;
    void setHandleSize(const int size);
    QSize getMinSize() const;
    void setMinSize(const QSize &size);
    QPen getPenFrame() const;
    void setPenFrame(const QPen &value);
    QPen getPenHandle() const;
    void setPenHandle(const QPen &value);
    QBrush getBrushHandle() const;
    void setBrushHandle(const QBrush &value);
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
    void adjustHandlePos();
    void adjustHandleSize();
    QPen penFrame;
    QPen penHandle;
    QBrush brushHandle;
};

#endif // RECTSELECTION_H
