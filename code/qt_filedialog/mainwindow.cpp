#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "open file dialog",
                   "./",
                   "All file(*.*);;C files(*.c);;Head files(*.h);;C++ files(*.cpp)");  //;; 分号隔开不同类型的文件
    ui->lineEdit->setText(s);
    if(s.size()>5)
    {
        QFile file(s);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<s<<" open fail!";
            return;
        }
        QByteArray line;
        ui->textBrowser->clear();
        while(!file.atEnd())
        {
            //line = file.readLine();
            //line=file.read(1024);
            //qDebug()<<line;
            line = file.readLine();
            ui->textBrowser->append(line);
        }
        file.close();
    }

}
