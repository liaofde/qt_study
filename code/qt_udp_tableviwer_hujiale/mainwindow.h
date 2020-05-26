#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include"bufferdata.h"
#include"condata.h"
#include<QStandardItemModel>
#include<QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
   void SetText(QString type,QString name);
    void timeout ( );
private:
    QStandardItemModel * modal;
    QTimer t;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
