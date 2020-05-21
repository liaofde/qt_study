#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();
    //connect(this, SIGNAL(readyRead()),this,SLOT(receive()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}


void MainWindow::on_pushButton_clicked()
{
    QString str = ui->pushButton->text();
    if(QString::compare(str,"连接",Qt::CaseInsensitive)==0)
    {
        qDebug()<<"open"   ;

        QString ip=ui->lineEdit->text();
        QHostAddress Address ;//借助QHostAddress判断输入的内容的格式是不是IP
        bool _isAddr= Address.setAddress(ip.trimmed()); //timmed是去掉空格

        int port=ui->lineEdit_2->text().toInt();

        if(_isAddr == false || port==0 || port>65535 )
        {
            qDebug()<<"ip or port invaild!";
            QMessageBox::warning(NULL, QStringLiteral("警告"), QStringLiteral("IP或端口设置错误！"), QMessageBox::Close, QMessageBox::Close);// 添加提示
        }
        else
        {


            socket->connectToHost(ip, port);
            //socket->connectToHost("192.168.0.191",6000);
            if(socket->waitForConnected())
            {
                socket->write("hello world");//转编码
                ui->pushButton->setText("关闭");
                ui->label_4->setText("Connected");
                connect(this->socket, SIGNAL(readyRead()),this,SLOT(receive()));
                connect(this->socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(stateChangedSloat(QAbstractSocket::SocketState)));
            }
        }
    }
    else
    {
        qDebug()<<"close";
        ui->pushButton->setText("连接");
        socket->disconnectFromHost();
    }

}

void MainWindow::receive()
{
    QByteArray msg;
    QString ip = socket->peerName();
    quint16 port = socket->peerPort();

    msg = socket->readAll();
    if(msg.size())
    {
        qDebug()<<"ip"<<ip<<",port"<<port<<"rec"<<msg;
        ui->textBrowser->append(msg);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    QString a;

    a=ui->lineEdit_3->text();

    if(a.size())
    {
        socket->write(a.toLatin1());
    }
}
/*
        UnconnectedState,
        HostLookupState,
        ConnectingState,
        ConnectedState,
        BoundState,
        ListeningState,
        ClosingState*/
void MainWindow::stateChangedSloat(QAbstractSocket::SocketState p)
{
    if(QAbstractSocket::SocketState::ClosingState == p)
    {
        qDebug()<<" close socket";

        ui->pushButton->setText("连接");
        ui->label_4->setText("Closing");
    }
    else if(QAbstractSocket::SocketState::ConnectedState == p)
    {
        ui->pushButton->setText("断开");
        ui->label_4->setText("Connected");
    }
    else if(QAbstractSocket::SocketState::ListeningState == p)
    {
        ui->label_4->setText("Listening");
    }
    else if(QAbstractSocket::SocketState::UnconnectedState == p)
    {
        ui->label_4->setText("Unconnected");
    }
    else if(QAbstractSocket::SocketState::ConnectingState == p)
    {
        ui->label_4->setText("Connecting");
    }
}
