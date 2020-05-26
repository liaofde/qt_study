#include "udpserver.h"
#include<QDebug>
UdpServer::UdpServer()
{

}

void UdpServer::timeout()
{
       //qDebug ( ) << "run " << QThread::currentThreadId ( );
    if (!BufferData::GetInstance ( )->isEmpty ( ))
    {
        QByteArray b = BufferData::GetInstance ( )->GetData ( );
        BufferData::GetInstance ( )->Remove ( );
        qDebug()<<b;
        socket->writeDatagram ( b , b.size ( ) , QHostAddress::Broadcast , 6000 );
    }
}

void UdpServer::DataReceive()
{
    QByteArray b ( ( int ) socket->pendingDatagramSize ( ) , '0' );
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram ( b.data ( ) , b.size ( ) , &sender , &senderPort );
    QString msg = QString::fromLocal8Bit ( b.data ( ) );
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson ( msg.toStdString ( ).data ( ) , &json_error );

    auto jsonObject = parse_doucment.object ( );
    qDebug ( ) << " Recv service :" << b <<" port :" << senderPort << " , ip:" << sender.toString ( );
    Slove(jsonObject);
}

void UdpServer::Slove(const QJsonObject &jsonObject)
{
    QStringList op;
    op<<jsonObject["IP"].toString()<<jsonObject["GW"].toString()<<jsonObject["MAC"].toString()<<jsonObject["NAME"].toString();
    if(!Has(jsonObject["IP"].toString()))
    {
        emit SetText("ADDROW",op.join(";"));
    }

}

void UdpServer::sltStateChanged(QAbstractSocket::SocketState state)
{

}

bool UdpServer::Has(QString na)
{
    if(ips.size()>0)
    {
        for(auto i:ips)
        {
            if(i==na)
            {
                return true;
            }
        }
    }
    ips.push_back(na);
    return false;
}

void UdpServer::run()
{
    this->socket = new QUdpSocket ( );
    socket->bind ( 8060 );
    socket->waitForConnected ( );
    qDebug ( ) << "run " << QThread::currentThreadId ( );

    connect ( this->socket , SIGNAL ( readyRead ( ) ) , this , SLOT ( DataReceive ( ) ) , Qt::DirectConnection );

    timer = new QTimer ( );
    connect ( this->timer , SIGNAL ( timeout ( ) ) , this , SLOT ( timeout ( ) ) , Qt::DirectConnection );
    timer->start ( 20 );
    exec ( );
}
