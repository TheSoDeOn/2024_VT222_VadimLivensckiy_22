#include "imageitem.h"
#include <QGridLayout>

ImageItem::ImageItem(QWidget *parent) : QWidget{parent}
{
    img = new QLabel(this);
    title = new QLabel(this);
    info = new QLabel(this);
    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(img, 0, 0);
    grid->addWidget(title, 0, 1);
    grid->addWidget(info, 1, 1);
    img->setText("pix");
    title->setText("title");
    info->setText("info");
}
