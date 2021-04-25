#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <dialog.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void disp_info_slot(QList<QStandardItem *> lst);
    void button_enable_slot();
signals:
    void push_button_signal(QStringList *);
    void update_signal(QStringList &);
private:
    QTimer *timer;
    QStandardItemModel *modle;
    QStringList *ip_list;
    int broadcast_flag = 0;

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
};
#endif // MAINWINDOW_H
