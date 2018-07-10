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
    void loadImage(QImage srcImg);
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
    QBrush getBrushSrcImgFrame() const;
    void setBrushSrcImgFrame(const QBrush &value);
    QImage getCroppedImg() const;
    QPixmap getCroppedImgPixmap();
    enum class ImageCroppedOutput { qImage, qPixmap, both };
    ImageCroppedOutput getCropOutput() const;
    void setCropOutput(const ImageCroppedOutput &value);

signals:
    void imageCropped(QImage croppedImg);
    void imageCropped(QPixmap croppedImgPixmap);
    void cropCleared(); //crop image is removed

public slots:
    void crop();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    qreal zoomAmount;
    int padding;
    QRect paddingRects[4];
    QImage srcImg; //implicitly shared object
    QImage croppedImg; //implicitly shared object
    QPixmap croppedImgPixmap;
    QBrush brushSrcImgFrame;
    QSize canvasSize;
    RectSelection cropArea;
    ImageCroppedOutput cropOutput;
};

#endif // CROPCANVAS_H
