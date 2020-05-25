#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui->comboBox->addItem(info.portName());
    ui->comboBox->addItem("刷新");

    serial =new QSerialPort(this);

    connect(serial, SIGNAL(readyRead()), this, SLOT(receive()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    qDebug()<<arg1;

    if(QString::compare("刷新",ui->comboBox->currentText()) == 0)
    {
        ui->comboBox->clear();
        const auto infos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : infos)
            ui->comboBox->addItem(info.portName());
        ui->comboBox->addItem("刷新");
        ui->comboBox->setCurrentIndex(0);
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<ui->comboBox->currentText();
    qDebug()<<ui->comboBox_2->currentText();
    qDebug()<<ui->comboBox_3->currentText();
    qDebug()<<ui->comboBox_4->currentText();
    qDebug()<<ui->comboBox_5->currentText();


    if(serial->isOpen())
    {
        serial->close();
        ui->groupBox->setEnabled(true);
        ui->pushButton->setText("打开");
    }
    else
    {
        QSerialPortInfo port(ui->comboBox->currentText());
        int baudrate = ui->comboBox_2->currentText().toUInt();

        QString stop_bit= ui->comboBox_4->currentText();
        QString check = ui->comboBox_5->currentText();

        serial->setPort(port);
        serial->setBaudRate(baudrate);
        switch(ui->comboBox_3->currentIndex())
        {
        case 5:serial->setDataBits(QSerialPort::Data5);
            break;
        case 6:serial->setDataBits(QSerialPort::Data6);
            break;
        case 7:serial->setDataBits(QSerialPort::Data7);
            break;
        default:serial->setDataBits(QSerialPort::Data8);
            break;
        }
        if(serial->open(QIODevice::ReadWrite))
        {
            ui->groupBox->setEnabled(false);
            ui->pushButton->setText("关闭");
        }
        else
        {
            qDebug()<<port.portName()<<" can't open!";
            QMessageBox::about(NULL, "提示", "串口无法打开\r\n不存在或已被占用");
        }


    }
}

void MainWindow::receive()
{
    QByteArray qb = serial->readAll();

    ui->textBrowser->append(qb);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = ui->textEdit->toPlainText();
    serial->write(str.toLatin1());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->clear();
    ui->textEdit->clear();
}
