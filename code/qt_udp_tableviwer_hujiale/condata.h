#ifndef CONDATA_H
#define CONDATA_H

#include<QByteArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<QString>

class ConData
{
public:
    ConData();
    static QJsonObject  GetCmd ( QString cmd )
    {
        QJsonObject re;
        re.insert ( "CMD" ,cmd  );
        return re;
    }

    static QByteArray GetByte ( QString cmd )
    {
        return QJsonDocument ( GetCmd ( cmd ) ).toJson ( );
    }

};

#endif // CONDATA_H
