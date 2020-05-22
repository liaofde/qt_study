#include "mainwindow.h"

#include <QApplication>
#include "m_udpcomm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    m_udpcomm mudp;

    QObject::connect(&mudp, SIGNAL(disp_signal(QByteArray &)), &w,SLOT(disp_slot(QByteArray &)));
    QObject::connect(&w,SIGNAL(send_signal(QString &,quint16,QByteArray &)), &mudp, SLOT(send_slot(QString &,quint16,QByteArray &)));

    return a.exec();
}
