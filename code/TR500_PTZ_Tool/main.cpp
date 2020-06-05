#include "mainwindow.h"

#include <QApplication>
#include "m_udpcomm.h"
#include "update_thread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("yt_tr500_ptz_tool");

    m_udpcomm mudp;
    update_thread m_update_thread;
    Dialog m_dialog;
    qRegisterMetaType<QStringList>("QStringList &");
    QObject::connect(&mudp, SIGNAL(disp_info_signal(QList<QStandardItem *>)), &w,SLOT(disp_info_slot(QList<QStandardItem *>)));
    QObject::connect(&w,SIGNAL(push_button_signal(QStringList *)), &mudp, SLOT(push_button_slot(QStringList *)));
    QObject::connect(&w,SIGNAL(update_signal(QStringList &)),&m_update_thread, SLOT(update_slot(QStringList &)));
    QObject::connect(&m_update_thread,SIGNAL(button_enable_signal()),&w,SLOT(button_enable_slot()));
    QObject::connect(&m_update_thread, SIGNAL(subdisp_signal(QStringList &)), &m_dialog, SLOT(subdisp_slot(QStringList &)));

    m_update_thread.start();
    return a.exec();
}
