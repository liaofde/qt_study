#include "mainwindow.h"

#include <QApplication>
#include <QList>
#include <QVector>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QVector<int> vector;
    qDebug()<<"QVector<int>:";
    //在末尾增加元素
    vector.push_back(3);
    vector<<4;
    vector.append(5);
    //在开头增加元素
    vector.prepend(2);
    vector.push_front(1);
    qDebug()<<vector;
    //任意位置插入
    vector.insert(1,2,6); //在索引值1的位置插入2个6
    qDebug()<<vector;
    //移除元素
    vector.remove(1,2); //从索引值1开始，移除2个元素
    qDebug()<<vector;
    //查找
    qDebug()<<vector.indexOf(3); //查找值为3的元素，返回找到的 第一个3 的索引值
    //按索引取出元素
    qDebug()<<vector.at(0);
    //更改元素
    vector.replace(0,2); //将索引值为0的元素替换成 2
    qDebug()<<vector;
    //获取长度，以下三种方式等价
    qDebug()<<vector.count();
    qDebug()<<vector.size();
    qDebug()<<vector.length();
    //清除容器
    vector.clear();
    qDebug()<<vector;

    QList<int> list;
    qDebug()<<"\n\nQList<int>:";
    //在末尾增加元素
    list.push_back(3);
    list<<4;
    list.append(5);
    //在开头增加元素
    list.prepend(2);
    list.push_front(1);
    qDebug()<<list;
    //任意位置插入
    list.insert(1,6); //在索引值1的位置插入6
    qDebug()<<list;
    //移除元素
    list.removeAt(1); //移除索引值为1的元素
    qDebug()<<list;
    //查找
    qDebug()<<list.indexOf(3); //查找值为3的元素，返回找到的 第一个3 的索引值
    //按索引取出元素
    qDebug()<<list.at(0);
    //更改元素
    list.replace(0,2); //将索引值为0的元素替换成 2
    qDebug()<<list;
    //获取长度，以下三种方式等价
    qDebug()<<list.count();
    qDebug()<<list.size();
    qDebug()<<list.length();
    //清除容器
    list.clear();
    qDebug()<<list;

    return a.exec();
}
