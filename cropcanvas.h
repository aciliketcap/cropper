#ifndef CROPCANVAS_H
#define CROPCANVAS_H

#include <QWidget>
#include "rectselection.h"

class CropCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit CropCanvas(QWidget *parent = nullptr);
    ~CropCanvas();
    void loadImage(QImage *srcImg);
    qreal getZoomAmount() const;
    void setZoomAmount(qreal newZoomAmount);
    //selection rectangle properties:
    int getCropAreaHandleSize() const;
    void setCropAreaHandleSize(int size);
    QSize getCropAreaMinSize() const;
    void setCropAreaMinSize(QSize size);
    QPen getCropAreaPenFrame() const;
    void setCropAreaPenFrame(const QPen &value);
    QPen getCropAreaPenHandle() const;
    void setCropAreaPenHandle(const QPen &value);
    QBrush getCropAreaBrushHandle() const;
    void setCropAreaBrushHandle(const QBrush &value);
    QImage *getCroppedImg() const;
    QPixmap getCroppedImgPixmap();
    QPoint getSrcImgPos() const;
    void setSrcImgPos(const QPoint &value);
    enum class ImageCroppedOutput { qImage, qPixmap, both };
    ImageCroppedOutput getCropOutput() const;
    void setCropOutput(const ImageCroppedOutput &value);

signals:
    void imageCropped(QImage croppedImg);
    void imageCropped(QPixmap croppedImgPixmap);

public slots:
    void crop();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    qreal zoomAmount;
    QPoint srcImgPos;
    QImage* srcImg;
    QImage* croppedImg;
    QPixmap croppedImgPixmap;
    RectSelection cropArea;
    ImageCroppedOutput cropOutput;
};

#endif // CROPCANVAS_H
