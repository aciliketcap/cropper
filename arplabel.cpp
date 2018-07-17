#include "arplabel.h"

//TODO: we can turn this into a general container later?
ArpLabel::ArpLabel(QWidget *parent) :
    QFrame(parent)
{
    this->setFrameStyle(QFrame::Box);
    this->setLayout(&HBL);
    HBL.addLayout(&VBL);
    VBL.addWidget(&image);
    image.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    image.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void ArpLabel::setPixmap(const QPixmap &img)
{
    originalImageSize = img.size();
    image.setPixmap(img);
    adjustImageSize(this->size());
}

void ArpLabel::clear()
{
    /* not implemented yet */
    return;
}

void ArpLabel::resizeEvent(QResizeEvent *event)
{
    adjustImageSize(event->size());
}

void ArpLabel::adjustImageSize(QSize frameSize)
{
    if(originalImageSize.width() > frameSize.width()
            || originalImageSize.height() > frameSize.height()) {
        double imgRatio = originalImageSize.width() / (double) originalImageSize.height();
        double areaRatio = frameSize.width() / (double) frameSize.height();

        if(imgRatio < areaRatio) {
            //image.resize(frameSize.height() * imgRatio, frameSize.height());
            QSize imgSize = QSize(frameSize.height() * imgRatio, frameSize.height());
            image.setMaximumSize(imgSize);
        } else {
            //image.resize(frameSize.width(), frameSize.width() / imgRatio);
            QSize imgSize = QSize(frameSize.width(), frameSize.width() / imgRatio);
            image.setMaximumSize(imgSize);
        }
        image.setScaledContents(true);
    } else {
        //set label size to minimum and disable scaling
        //image.resize(originalImageSize);
        image.setMaximumSize(originalImageSize);
        image.setScaledContents(false);
    }
}
