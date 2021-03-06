#ifndef BUFFERDATA_H
#define BUFFERDATA_H
#include<thread>
#include<mutex>
#include<queue>
#include<QByteArray>
#include<QString>
using std::queue;
using std::recursive_mutex;
#include<QDebug>
#include<QObject>

class   BufferData 
{
public:
    static BufferData* GetInstance ( )
	{
		if ( bufferData == nullptr )
		{
			bufferData = new BufferData ( );
		}
		return bufferData;
	}
	void Add ( const QByteArray& data );
	QByteArray GetData ( );
	void Remove ( );
	bool isEmpty ( );

protected:
	BufferData ( )
	{

	}
	static BufferData* bufferData;
	queue<QByteArray> datas;
	recursive_mutex lock;
};

#endif // BUFFERDATA_H
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
