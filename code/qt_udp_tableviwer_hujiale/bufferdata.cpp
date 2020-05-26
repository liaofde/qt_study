
#include "bufferdata.h"

 BufferData* BufferData::bufferData = nullptr;

void BufferData::Add ( const QByteArray& data )
{
	lock.lock ( );
	datas.push ( data );
	lock.unlock ( );
}

QByteArray BufferData::GetData ( )
{
	lock.lock ( );
	const auto x = datas.front ( );
	lock.unlock ( );
	return x;
}

void BufferData::Remove ( )
{
	lock.lock ( );
	datas.pop ( );
	lock.unlock ( );
}

bool BufferData::isEmpty ( )
{
	lock.lock ( );
	const auto x = datas.empty ( );
	lock.unlock ( );
	return x;
}
