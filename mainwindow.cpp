#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include "imageitem.h"
#include <QSettings>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new QLabel(this);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    ui->scrollArea->setWidget(imageLabel);

    // Загрузка пути к последнему открытому файлу
    QSettings settings("MyCompany", "MyApp");
    QString lastOpenedFile = settings.value("lastOpenedFile").toString();
    if (!lastOpenedFile.isEmpty()) {
        QPixmap pix(lastOpenedFile);
        imageLabel->setPixmap(pix);
        imageLabel->setFixedSize(pix.size());
        setImagesList(lastOpenedFile);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выбрать изображение", "",
                                                    "Изображения (*.bmp *.jpg *.png)");
    if (!fileName.isEmpty()) {
        QPixmap pix(fileName);
        imageLabel->setPixmap(pix);
        imageLabel->setFixedSize(pix.size());
        setImagesList(fileName);

        // Сохранение пути к последнему открытому файлу
        QSettings settings("MyCompany", "MyApp");
        settings.setValue("lastOpenedFile", fileName);
    }
}


void MainWindow::on_action_3_triggered()
{
    this->close();
}

void MainWindow::on_action_4_triggered()
{
    int newWidth = int(imageLabel->width()*1.25);
    int newHeight = int(imageLabel->height()*1.25);
    imageLabel->setFixedSize(newWidth,newHeight);
}

void MainWindow::on_action_5_triggered()
{
    int newWidth = int(imageLabel->width()*0.75);
    int newHeight = int(imageLabel->height()*0.75);
    imageLabel->setFixedSize(newWidth,newHeight);
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
