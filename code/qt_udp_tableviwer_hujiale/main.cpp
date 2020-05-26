#include "mainwindow.h"
#include <QApplication>
#include"udpserver.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    UdpServer  udp ;
    udp.start();
    QObject::connect(&udp,SIGNAL(SetText(QString,QString)),&w,SLOT(SetText(QString,QString)) ,Qt::DirectConnection);
    return a.exec();
}
