#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    connect ( &t , SIGNAL ( timeout ( ) ) , this , SLOT ( timeout ( ) ) , Qt::DirectConnection );
    ui->setupUi(this);
    modal=new QStandardItemModel(0,4);

    QStringList column, row;

    column << "IP" << "GW" << "MAC" << "NAME";
    modal->setHorizontalHeaderLabels(column);                // 设置水平表头标签
    //modal->setVerticalHeaderLabels(row);                     // 设置垂直表头标签
    //    for (int i = 0; i < 4; ++i)
    //        for (int j = 0; j < 4; ++j)
    //            modal->setItem(i, j, new QStandardItem(QString("%1").arg(i + j)));
    ui->tableView->setModel(modal);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    t.start(1000);
    ui->pushButton->setEnabled(false);
}

void MainWindow::SetText(QString type, QString name)
{
    //ui->tableView->
    if("ADDROW"==type)
    {
        QList<QStandardItem *> lsi;
        auto ks= name.split(";");
        lsi.append(new QStandardItem(ks[0]));
        lsi.append(new QStandardItem(ks[1]));
        lsi.append(new QStandardItem(ks[2]));
        lsi.append(new QStandardItem(ks[3]));
        modal->appendRow(lsi);
    }
}

void MainWindow::timeout()//
{
    BufferData::GetInstance ( )->Add(ConData::GetByte("sousuo"));
}
