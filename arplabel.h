#ifndef ARPLABEL_H
#define ARPLABEL_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QLabel>

class ArpLabel : public QFrame
{
    Q_OBJECT
public:
    explicit ArpLabel(QWidget *parent = nullptr);

signals:

public slots:
    void setPixmap(const QPixmap &img);
    void clear();

protected:
    void adjustImageSize(QSize frameSize);
    void resizeEvent(QResizeEvent *event);

private:
    QHBoxLayout HBL;
    QVBoxLayout VBL;
    QLabel image;
    QSize originalImageSize;
};

#endif // ARPLABEL_H
