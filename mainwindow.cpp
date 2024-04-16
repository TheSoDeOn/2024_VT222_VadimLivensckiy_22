#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include "imageitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new QLabel(this);
    imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    ui->scrollArea->setWidget(imageLabel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                       "Выбрать изображение", "",
                        "Изображения (*.bmp  *.jpg *.png)");
    QPixmap pix(fileName);
    imageLabel->setPixmap(pix);
    imageLabel->setFixedSize(pix.width(),pix.height());
    setImagesList(fileName);

}

void MainWindow::on_action_3_triggered()
{
    this->close();
}

void MainWindow::setImagesList(QString filename)
{
    ui->listWidget->clear();  // предварительно удаляем все элементы из списка
    QFileInfo info(filename);  // получаем объект с инфой о файле
    QDir dir(info.absolutePath()); // получаем абсолютный путь и создаёт объект класса для работы с папками
    QStringList filter;
    filter << "*.jpg" << "*.png" << "*.bmp";
    QFileInfoList list =  dir.entryInfoList(filter);
    for (int i=0;i<list.count();i++) {
        QFileInfo f = list.at(i);
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ImageItem *imgitem = new ImageItem;
        QPixmap pix(f.filePath());
        imgitem->setData(pix.scaledToWidth(80, Qt::SmoothTransformation), f.fileName(), QString::number(f.size()));
        item->setSizeHint(imgitem->sizeHint());
        ui->listWidget->setItemWidget(item, imgitem);
    }
}
