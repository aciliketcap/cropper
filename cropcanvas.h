#ifndef CROPCANVAS_H
#define CROPCANVAS_H

#include <QWidget>
#include "rectselection.h"

class CropCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit CropCanvas(QWidget *parent = nullptr);
    void loadImage(QImage *srcImg);
    qreal getZoomAmount() const { return zoomAmount; }
    void setZoomAmount(qreal newZoomAmount);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    qreal zoomAmount;
    QImage* srcImg;
    RectSelection cropArea;
};

#endif // CROPCANVAS_H
