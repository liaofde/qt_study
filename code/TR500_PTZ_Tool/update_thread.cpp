#include "update_thread.h"
#include "QDebug"
#include "QProcess"
#include "QApplication"

update_thread::update_thread(QObject *parent)
    :QThread(parent)
{
    update_msg.clear();

}

void update_thread::run()
{
    QStringList msg;
    while(1)
    {
        msleep(250);
        mutex.lock();
        if(update_msg.isEmpty()==false)
        {
            QProcess* caller = new QProcess(this);//创建对象，指定父类指针

            msg.clear();
            msg<<"正在升级,请稍侯...\n"<<"正在升级";
            emit subdisp_signal(msg);

            caller->start("update.exe",update_msg);//启动程序并传入参数
            caller->start("ping.exe",QStringList()<<"192.168.0.124");//启动程序并传入参数
            if(caller->waitForStarted(3000)==false)
            {
                msg.clear();
                msg<<"错误!找不到update.exe升级程序\n"<<"错误";
                emit subdisp_signal(msg);
                emit button_enable_signal();
                update_msg.clear();
                return;
            }

        #if 0
            caller->waitForFinished();
        #else
            int tv=0;
            while(false == caller->waitForFinished(1000))
            {
                QString strTemp=QString::fromLocal8Bit(caller->readAllStandardOutput());
                if(!strTemp.isEmpty())
                {
                    msg.clear();
                    msg<<strTemp;
                    emit subdisp_signal(msg);
                    qDebug()<<strTemp;
                }
                QApplication::processEvents();
                tv++;
                if(tv>20)
                {
                    caller->kill();
                    msg.clear();
                    msg<<"升级超时，退出升级\n"<<"提示";
                    emit subdisp_signal(msg);
                    emit button_enable_signal();
                    update_msg.clear();
                    return;
                }

            }
        #endif
            QString strTemp=QString::fromLocal8Bit(caller->readAllStandardOutput());
            if(!strTemp.isEmpty())
            {
                msg.clear();
                msg<<strTemp;
                emit subdisp_signal(msg);
            }

            if(strTemp.indexOf("iap reboot") > 0)
            {
                strTemp="升级成功";
                msg.clear();
                msg<<strTemp<<"升级成功";
                emit subdisp_signal(msg);
            }
            else
            {
                strTemp="升级失败";
                msg.clear();
                msg<<strTemp<<"升级失败";
                emit subdisp_signal(msg);
            }

            emit button_enable_signal();
            update_msg.clear();
        }
        mutex.unlock();
    }
}

void update_thread::update_slot(QStringList &lst)
{

    mutex.lock();
    for(int i=0;i<lst.size();i++)
        update_msg.append(QString(lst.at(i)));
    mutex.unlock();
}

