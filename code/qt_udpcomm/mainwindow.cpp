#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDateTime"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::disp_slot(QByteArray &msg)
{
    QString disp;
    QDateTime tim;

    tim = QDateTime::currentDateTime();
    disp = tim.toString("hh:mm:ss");
    disp += "接收数据：";
    disp += msg;
    ui->textBrowser->append(disp);
    this->rxcnt += msg.size();
    ui->label_3->setText(QString("收：%1字节, 发：%2字节").arg(this->rxcnt).arg(this->txcnt));
}



void MainWindow::on_pushButton_clicked()
{
    QByteArray qb;
    QString ip;
    quint16 port;
    QDateTime tim;
    QString disp;

    ip = ui->lineEdit_2->text();
    port = ui->lineEdit_3->text().toUInt();
    qb = ui->lineEdit->text().toLocal8Bit();
    emit send_signal(ip,port,qb);

    tim = QDateTime::currentDateTime();
    disp = tim.toString("hh:mm:ss");
    disp += "发送数据：";
    disp += qb;
    ui->textBrowser->append(disp);
    this->txcnt += qb.size();
    ui->label_3->setText(QString("收：%1字节, 发：%2字节").arg(this->rxcnt).arg(this->txcnt));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    this->rxcnt = 0;
    this->txcnt = 0;
    ui->label_3->setText(QString("收：%1字节, 发：%2字节").arg(this->rxcnt).arg(this->txcnt));
}
