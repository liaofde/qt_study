#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>

#define USE_SIGNAL

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
public:
    QStandardItemModel *modle;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

#ifdef USE_SIGNAL
signals:
    void insert_signal(QList<QStandardItem *>);
public slots:
    void insert_slot(QList<QStandardItem *>);
#endif
};
#endif // MAINWINDOW_H
