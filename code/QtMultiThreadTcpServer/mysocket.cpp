#include "mysocket.h"
#include "QDebug"

MySocket::MySocket(int sockDesc, QObject *parent) :
    QTcpSocket(parent),
    m_sockDesc(sockDesc)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(recvData()));
}

MySocket::~MySocket()
{

}

void MySocket::sendData(int id, const QByteArray &data)
{
    if (id == m_sockDesc && !data.isEmpty()) {
        this->write(data);
    }
}

void MySocket::recvData(void)
{
    QString ip = peerName();//peerAddress().toString().remove(0, 7);
    quint16 port = peerPort();
    QByteArray data = readAll();

    qDebug()<<"ip:"<<ip<<"port:"<<port<<"rec:"<<data;

    emit dataReady(ip, data);
}
