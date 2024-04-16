#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class ImageItem : public QWidget
{
    Q_OBJECT
public:
    explicit ImageItem(QWidget *parent = nullptr);

signals:
private:
    QLabel *img;
    QLabel *title;
    QLabel *info;
};

#endif // IMAGEITEM_H
