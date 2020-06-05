#ifndef UPDATE_THREAD_H
#define UPDATE_THREAD_H

#include <QThread>
#include <QObject>
#include <QWidget>
#include <QStringList>
#include <dialog.h>
#include <QMutex>

class update_thread:public QThread
{
    Q_OBJECT
public:
    update_thread(QObject *parent=0);
public:
    void run();
public slots:
    void update_slot(QStringList &);
signals:
    void subdisp_signal(QStringList &);
    void button_enable_signal();

private:
    QMutex mutex;
    QStringList update_msg;
};

#endif // UPDATE_THREAD_H
