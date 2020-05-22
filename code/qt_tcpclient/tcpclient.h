#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>


class tcpclient:public QTcpSocket
{
    Q_OBJECT
public:
    tcpclient(QObject *parent = Q_NULLPTR);
};

#endif // TCPCLIENT_H
