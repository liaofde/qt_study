#ifndef M_UDPCOMM_H
#define M_UDPCOMM_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QUdpSocket>
#include <QStandardItem>
#include <QList>

#define UDP_PORT 8000

class m_udpcomm:public QWidget
{
    Q_OBJECT
public:
    m_udpcomm(QWidget *p=Q_NULLPTR);
    ~m_udpcomm();
public slots:
    void receive_slot();
    void push_button_slot(QStringList *);
signals:
    void disp_info_signal(QList<QStandardItem *> lst);
public:
    QUdpSocket *socket=0;
};

#endif // M_UDPCOMM_H
