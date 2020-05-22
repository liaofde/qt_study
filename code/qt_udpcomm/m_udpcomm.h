#ifndef M_UDPCOMM_H
#define M_UDPCOMM_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QUdpSocket>


class m_udpcomm:public QWidget
{
    Q_OBJECT
public:
    m_udpcomm(QWidget *p=Q_NULLPTR);
    ~m_udpcomm();
public slots:
    void receive_slot();
    void send_slot(QString &ip, quint16 port, QByteArray &msg);
signals:
    void disp_signal(QByteArray &);
public:
    QUdpSocket *socket=0;
};

#endif // M_UDPCOMM_H
