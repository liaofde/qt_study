#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "QDebug"
#include "QWidget"
#include "QObject"
#include <qhostaddress.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void receive();
    void on_pushButton_2_clicked();
    void stateChangedSloat(QAbstractSocket::SocketState SocketState);
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
public:
    QTcpSocket *socket;
    uint64_t rxcnt=0;
    uint64_t txcnt=0;
};
#endif // MAINWINDOW_H
