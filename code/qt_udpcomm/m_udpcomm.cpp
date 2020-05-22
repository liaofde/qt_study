#include "m_udpcomm.h"

m_udpcomm::m_udpcomm(QWidget *p)
    :QWidget(p)
{
    this->socket = new QUdpSocket(this);
    this->socket->bind(10000);
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(receive_slot()), Qt::DirectConnection);
    //this->socket->writeDatagram("hello world!", QHostAddress::Broadcast, 60000);
}

m_udpcomm::~m_udpcomm()
{
    this->socket->close();

    delete this->socket;
}

void m_udpcomm::receive_slot()
{
    QByteArray rb;
    QHostAddress ip;
    quint16 port;

    rb.resize(socket->pendingDatagramSize());
    socket->readDatagram(rb.data(), rb.size(), &ip, &port);

    qDebug()<<"receive data"<<rb<<",size:"<<rb.size()<<",ip:"<<ip.toString().remove(0,7)<<",port:"<<port;
    emit disp_signal(rb);
}

void m_udpcomm::send_slot(QString &ip, quint16 port, QByteArray &msg)
{
    QHostAddress host(ip);

    this->socket->writeDatagram(msg, host, port);
}
