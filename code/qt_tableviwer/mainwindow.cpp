#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modal=new QStandardItemModel(0,5);

    QStringList header;

    header << "NAME" << "IP" << "GW" << "MASK" << "MAC"  ;
    modal->setHorizontalHeaderLabels(header);                // 设置水平表头标签
    ui->tableView->setModel(modal);
    ui->tableView->setColumnWidth(0,130);
    ui->tableView->setColumnWidth(1,120);
    ui->tableView->setColumnWidth(2,120);
    ui->tableView->setColumnWidth(3,120);
    ui->tableView->setColumnWidth(4,150);
/*
    QStringList content;
    content<<"192.168.0.191"<<"192.168.0.1"<<"00-00-00-00-00-01"<<"tr500_ptz";

    QList<QStandardItem *> lsi;
    auto ks= content;
    lsi.append(new QStandardItem(ks[0]));
    lsi.append(new QStandardItem(ks[1]));
    lsi.append(new QStandardItem(ks[2]));
    lsi.append(new QStandardItem(ks[3]));
    modal->appendRow(lsi);
*/
    QList<QStandardItem *> lsi;
    lsi.append(new QStandardItem("tr500_ptz"));
    lsi.append(new QStandardItem("192.168.0.191"));
    lsi.append(new QStandardItem("192.168.0.1"));
    lsi.append(new QStandardItem("255.255.255.0"));
    lsi.append(new QStandardItem("00-00-00-00-00-01"));
    modal->appendRow(lsi);

    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_tableView_clicked(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QList<QStandardItem *> lsi;
    lsi.append(new QStandardItem(ui->lineEdit->text()));
    lsi.append(new QStandardItem(ui->lineEdit_2->text()));
    lsi.append(new QStandardItem(ui->lineEdit_3->text()));
    lsi.append(new QStandardItem(ui->lineEdit_4->text()));
    lsi.append(new QStandardItem(ui->lineEdit_5->text()));
    modal->appendRow(lsi);
}

void MainWindow::on_pushButton_2_clicked()
{
    modal->removeRow(this->mindex.row());
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    this->mindex = index;
    qDebug()<<"row:"<<index.row()<<"column:"<<index.column();
    qDebug()<<"width:"<<ui->tableView->columnWidth(index.column());
}
