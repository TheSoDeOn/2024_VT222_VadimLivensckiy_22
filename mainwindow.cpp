#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

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
    ui->listWidget->clear();
    QFileInfo info(filename);
    QDir dir(info.absolutePath());
    QStringList filter;
    filter << "*.jpg" << "*.png" << "*.bmp";
    QFileInfoList list =  dir.entryInfoList(filter);
    for (int i=0;i<list.count();i++) {
        qDebug() << list.at(i).filePath();
        QFileInfo f = list.at(i);
        QIcon icon;
        icon.addFile(f.filePath());
        QListWidgetItem *item = new QListWidgetItem(icon, f.fileName());
        ui->listWidget->addItem(item);
        if(f.filePath() == filename){
            item->setSelected(true);
        }
    }
}
