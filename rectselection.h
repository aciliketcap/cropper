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
    void reinit();
    void draw(QPainter &painter);
    //TODO: I may turn these to events if I decide to make selection tool a seperate widget
    void pressed(const QPoint &pos);
    void moved(const QPoint &pos);
    void released(const QPoint &pos);
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
    QRect getFrame() const;

private:
    QSize minSize;
    bool minSizeSetManually; //if false use handleSize*2 as min
    void setDefaultMinSize();
    int handleSize;
    QRect frame;
    QRect tl, tr, bl, br;
    enum class Pressed { frame, tl, tr, bl, br, none };
    Pressed curPressed = Pressed::none;
    QPoint lastPressedPos;
    void adjustHandlePos();
    void adjustHandleSize();
    QPen penFrame;
    QPen penHandle;
    QBrush brushHandle;
};

#endif // RECTSELECTION_H
