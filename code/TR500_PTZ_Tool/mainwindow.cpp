#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QProcess"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ip_list = new QStringList();

    QStringList headlist;

    headlist<<"名称"<<"ip址址"<<"子网掩码"<<"网关"<<"MAC址址";
    modle = new QStandardItemModel(0,5);
    modle->setHorizontalHeaderLabels(headlist);
    ui->tableView->setModel(modle);

    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,100);
    ui->tableView->setColumnWidth(4,140);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ip_list;
    delete modle;
}

void MainWindow::disp_info_slot(QList<QStandardItem *> lst)
{
    int i;
    int res=-1;
    QString a;
    QString b = lst.takeAt(0)->text();

    for (i=0;i<ip_list->size();i++) {
        a=ip_list->at(i);
        if(QString::compare(a,b)==0)
        {
            ip_list->removeAt(i);
            ip_list->insert(i,b);
            modle->removeRow(i);
            modle->insertRow(i,lst);
            res=0;
            break;
        }
    }
    if(res==-1)
    {
        modle->appendRow(lst);
        ip_list->append(b);
    }

}

void MainWindow::button_enable_slot()
{
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::on_pushButton_1_clicked()
{
    QString ip="255.255.255.255";
    QString cmd="search";

    ip_list->clear();
    modle->removeRows(0,modle->rowCount());

    QStringList *info= new QStringList();
    info->append(ip);
    info->append(cmd);
    emit push_button_signal(info);
    delete info;
}

void MainWindow::on_pushButton_4_clicked()
{
    QString isBroadcast;
    QString ip;
    QString cmd="reboot";

    int i = ui->tableView->currentIndex().row();
    if(i<0)
        return;
    ip=ip_list->at(i);
    QStringList *info= new QStringList();
    info->append(ip);
    info->append(cmd);

    qDebug()<<"reboot ip:"<<ip;

    emit push_button_signal(info);
    delete info;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString ip;
    QString cmd="net_config";
    QString _ip;
    QString _mask;
    QString _gw;
    QString _mac;

    QModelIndex index=ui->tableView->currentIndex();
    int i = index.row();
    if(i<0)
        return;
    ip=ip_list->at(i);

    QStringList *info= new QStringList();

    info->append(ip);
    info->append(cmd);
    info->append(modle->item(i,1)->text());
    info->append(modle->item(i,2)->text());
    info->append(modle->item(i,3)->text());
    info->append(modle->item(i,4)->text());

    emit push_button_signal(info);
    delete info;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString ip;
    QString cmd="restore";

    int i = ui->tableView->currentIndex().row();
    if(i<0)
        return;
    ip=ip_list->at(i);
    QStringList *info= new QStringList();
    info->append(ip);
    info->append(cmd);

    qDebug()<<"reboot ip:"<<ip;

    emit push_button_signal(info);
    delete info;
}


void MainWindow::on_pushButton_6_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "open file dialog",
                   "./",
                   "bin files(*.bin);;all files(*.*)");  //;; 分号隔开不同类型的文件
    ui->lineEdit->setText(s);
    if(s.size()>5)
    {
        QFile file(s);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<s<<" open fail!";
            return;
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString ip;
    QString file=ui->lineEdit->text();
    int i;

    if(file.size()<5)
        return;
    if((i=ui->tableView->currentIndex().row())<0)
    {
        QMessageBox::information(NULL, "提示", "请选择要升级的设备");
         return;
    }
    if(i>=ip_list->size())
        return;
    ui->pushButton_5->setEnabled(false);
    //qApp->processEvents();

    QString fileName = QCoreApplication::applicationDirPath();
    qDebug()<<fileName;

    QStringList list;
    list<<"-a"<<ip_list->at(i)<<"-f"<<ui->lineEdit->text();
    emit update_signal(list);

}
