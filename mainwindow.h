#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();

private:
    Ui::MainWindow *ui;
    QLabel * imageLabel;
    void setImagesList(QString filename);
};

#endif // MAINWINDOW_H
