#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonArray>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    QString msg = "{\"name\":\"fred\",\"class\":\"991k\"}";
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson ( msg.toStdString ( ).data ( ) , &json_error );

    if(!parse_doucment.isNull() && json_error.error == QJsonParseError::NoError)
    {
        qDebug()<<"msg is json format";
        auto jsonObject = parse_doucment.object ( );
        QJsonValue val;

        if(true == jsonObject.contains("name"))
        {
            //qDebug()<<"name:"<<jsonObject["name"].toString();
            val = jsonObject.value("name");
            if(true == val.isString())
                qDebug()<<"name:"<<val.toString();
        }
        if(true == jsonObject.contains("class"))
        {
            qDebug()<<"class:"<<jsonObject["class"].toString();
        }

        val = jsonObject.value("name1");
        if(true == val.isUndefined())
            qDebug()<<"name1 is isUndefined";
    }

    QVariantHash data;
    QVariantHash subData1;
    QVariantHash subData2;
    /*子json对像添加子项*/
    subData1.insert("name", "apple");
    subData1.insert("icon", "appleIcon");
    subData1.insert("describe", "an apple");

    data.insert("first fruit", subData1);//加入到data

    subData2.insert("name", "orange");
    subData2.insert("icon", "orangeIcon");
    subData2.insert("describe", "an orange");

    data.insert("second fruit", subData2);

    QJsonArray array1;
    for (int i = 0; i < 5;i++)
    {
        array1.insert(i, QString::fromLocal8Bit("eat %1").arg(i));
    }
    data.insert("three fruit array", array1);

    QJsonObject rootObj = QJsonObject::fromVariantHash(data);


    /*删除json对像*/
    rootObj.remove("second fruit");

    /*删除json子对像中的关键字项*/
    QJsonValue val;
    val = rootObj.value("first fruit");
    if(true == val.isObject())
    {
        QJsonObject obj = val.toObject();
        obj.remove("describe");
        rootObj.remove("first fruit");
        rootObj.insert("first fruit",QJsonValue(obj));
    }
    /*QJson 子对象中加入数组*/
    QJsonObject subobj;
    subobj.insert("xxx","aaa");
    QJsonArray array;
    array.insert(0,"0");
    array.insert(1,"1");
    subobj.insert("array",QJsonValue(array));
    rootObj.insert("hhh",QJsonValue(subobj));

    /*json文件输出*/
    QJsonDocument document;
    document.setObject(rootObj);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);

    //根据实际填写路径
    QFile file(".\\1.json");
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
        qDebug() << "file error!";
    }
    QTextStream in(&file);
    in << json_str;
    file.close();   // 关闭file

    qDebug()<<json_str;

    return a.exec();
}
