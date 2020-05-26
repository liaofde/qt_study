#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList headlist;
    headlist<<"姓名"<<"班级"<<"学号";
    modle = new QStandardItemModel(0,3);
    modle->setHorizontalHeaderLabels(headlist);
    ui->tableView->setModel(modle);

    QList<QStandardItem *> lst;
    lst.append(new QStandardItem("廖芳德"));
    lst.append(new QStandardItem("965"));
    lst.append(new QStandardItem("19"));
    modle->appendRow(lst);

#ifdef USE_SIGNAL
    connect(this, SIGNAL(insert_signal(QList<QStandardItem *>)),this,SLOT(insert_slot(QList<QStandardItem *>)));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
    delete modle;
}


void MainWindow::on_pushButton_clicked()
{
    QList<QStandardItem *> lst;

    lst.append(new QStandardItem(ui->lineEdit->text()));
    lst.append(new QStandardItem(ui->lineEdit_2->text()));
    lst.append(new QStandardItem(ui->lineEdit_3->text()));
    modle->appendRow(lst);
}

void MainWindow::on_pushButton_2_clicked()
{
    QModelIndex index;
    index = ui->tableView->currentIndex();
    modle->removeRow(index.row());
}

void MainWindow::on_pushButton_3_clicked()
{
#ifdef USE_SIGNAL
    QList<QStandardItem *> lst;

    lst.append(new QStandardItem(ui->lineEdit->text()));
    lst.append(new QStandardItem(ui->lineEdit_2->text()));
    lst.append(new QStandardItem(ui->lineEdit_3->text()));
    emit insert_signal(lst);
#else
    QModelIndex index;
    QList<QStandardItem *> lst;

    lst.append(new QStandardItem(ui->lineEdit->text()));
    lst.append(new QStandardItem(ui->lineEdit_2->text()));
    lst.append(new QStandardItem(ui->lineEdit_3->text()));

    index = ui->tableView->currentIndex();
    modle->insertRow(index.row(),lst);
#endif

}

#ifdef USE_SIGNAL
void MainWindow::insert_slot(QList<QStandardItem *> lst)
{
     QModelIndex index;
     index = ui->tableView->currentIndex();
     modle->insertRow(index.row(),lst);
}
#endif
