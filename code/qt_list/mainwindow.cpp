#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringListModel"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList num;

    num <<QString("1")<<QString("2")<<QString("3");
    model = new QStringListModel(num);

    //model->sort(0);
    ui->listView->setModel(model);

    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->row = model->rowCount();
    QString str=ui->lineEdit->text();

    if(str.size()>0)
    {
        model->insertRows(model->rowCount(),1);
        QModelIndex index= model->sibling(this->row,0,index);
        model->setData(index,ui->lineEdit->text());
    }
    else
    {
        QMessageBox msg;
        msg.setText("input invaild!");
        msg.exec();
    }
}

void MainWindow::showClick(QModelIndex index)
{
    this->index = index;
    this->row=index.row();
}

void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(this->row);
}

void MainWindow::on_pushButton_5_clicked()
{
    model->removeRows(0,model->rowCount());
}

void MainWindow::on_pushButton_3_clicked()
{
    QString str=ui->lineEdit->text();

    if(str.size()>0)
    {
        model->insertRows(this->row,1);
        model->setData(this->index,str);
    }
    else
    {
        QMessageBox msg;
        msg.setText("input invaild!");
        msg.exec();
    }
}
