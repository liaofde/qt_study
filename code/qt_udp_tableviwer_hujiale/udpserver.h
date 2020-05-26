#ifndef UDPSERVER_H
#define UDPSERVER_H

#include<QUdpSocket>
#include<QThread>
#include"condata.h"
#include"bufferdata.h"
#include<QTimer>
#include<QVector>
class UdpServer:public QThread
{
    Q_OBJECT
public:
    UdpServer();
signals:
    void SetText(QString type,QString name);
public slots:
    void timeout ( );
    void DataReceive ( );
    void Slove(const QJsonObject& p);
    void sltStateChanged ( QAbstractSocket::SocketState state );
    bool Has(QString na);

protected:
    QVector<QString> ips;
    QUdpSocket* socket , * nextSocket;
    QTimer* timer;
    void run ( );
};

#endif // UDPSERVER_H
