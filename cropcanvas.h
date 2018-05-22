#ifndef CROPCANVAS_H
#define CROPCANVAS_H

#include <QWidget>

class CropCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit CropCanvas(QWidget *parent = nullptr);
    void loadImage(const QImage *srcImg);
    const QImage* srcImg;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
private:

};

#endif // CROPCANVAS_H
