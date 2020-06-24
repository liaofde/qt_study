#include "m_udpcomm.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

m_udpcomm::m_udpcomm(QWidget *p)
    :QWidget(p)
{
    this->socket = new QUdpSocket(this);
    //this->socket->bind(10000);
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(receive_slot()), Qt::DirectConnection);

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
    QString remote_ip;
    quint16 port;

    rb.resize(socket->pendingDatagramSize());
    socket->readDatagram(rb.data(), rb.size(), &ip, &port);
    remote_ip = ip.toString().remove(0,7);

    qDebug()<<"receive data"<<rb<<",size:"<<rb.size()<<",ip:"<<ip.toString().remove(0,7)<<",port:"<<port;

    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson ( rb.toStdString ( ).data ( ) , &json_error );

    if(!parse_doucment.isNull() && json_error.error == QJsonParseError::NoError)
    {
        auto jsonObject = parse_doucment.object ( );
        QJsonValue val;
        QString cmd_val;

        if(true == jsonObject.contains("cmd"))
        {
            QList<QStandardItem *> lst;
            val = jsonObject.value("cmd");
            lst.append(new QStandardItem(remote_ip));
            if(true == val.isString())
            {
                cmd_val = val.toString();
                qDebug()<<"cmd:"<<val.toString();

                if(QString::compare(cmd_val,"search_echo") == 0)
                {
                    if(true == jsonObject.contains("dev"))
                    {
                        qDebug()<<"dev:"<<jsonObject["dev"].toString();
                        lst.append(new QStandardItem(jsonObject["dev"].toString()));
                    }
                    else
                        return;

                    if(true == jsonObject.contains("ip"))
                    {
                        qDebug()<<"ip:"<<jsonObject["ip"].toString();
                        lst.append(new QStandardItem(jsonObject["ip"].toString()));
                    }
                    else
                        return;
                    if(true == jsonObject.contains("mask"))
                    {
                        qDebug()<<"mask:"<<jsonObject["mask"].toString();
                        lst.append(new QStandardItem(jsonObject["mask"].toString()));
                    }
                    else
                        return;
                    if(true == jsonObject.contains("gw"))
                    {
                        qDebug()<<"gw:"<<jsonObject["gw"].toString();
                        lst.append(new QStandardItem(jsonObject["gw"].toString()));
                    }
                    else
                        return;
                    if(true == jsonObject.contains("mac"))
                    {
                        qDebug()<<"mac:"<<jsonObject["mac"].toString();
                        lst.append(new QStandardItem(jsonObject["mac"].toString()));
                    }
                    else
                        return;
                    emit disp_info_signal(lst);
                }
            }
        }
    }
}

void m_udpcomm::push_button_slot(QStringList *info)
{
    QHostAddress host(info->at(0));
    QJsonObject rootObj;
    QString cmd(info->at(1));
    int res = -1;
    int num = 1;

    if(QString::compare(cmd,"search")==0)
    {
        rootObj.insert("cmd", "search");
        num=5;
        res = 0;
    }
    else if(QString::compare(cmd,"reboot")==0)
    {
        rootObj.insert("cmd", "reboot");
        res = 0;
    }
    else if(QString::compare(cmd,"restore")==0)
    {
        rootObj.insert("cmd", "restore");
        res = 0;
    }
    else if(QString::compare(cmd,"net_config")==0)
    {
        rootObj.insert("cmd", "net_config");
        rootObj.insert("ip", info->at(2));
        rootObj.insert("mask", info->at(3));
        rootObj.insert("gw", info->at(4));
        rootObj.insert("mac", info->at(5));
        res = 0;
    }
    if(res==0)
    {
        QJsonDocument document;
        document.setObject(rootObj);
        QByteArray byte_array = document.toJson(QJsonDocument::Compact);
        QString json_str(byte_array);
        for (int i=0;i<num;i++) {
            this->socket->writeDatagram(json_str.toLatin1(), host, UDP_PORT);
        }

    }
}
