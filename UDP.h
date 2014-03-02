#ifndef __UDP_H__
#define __UDP_H__

#include "ProtoBase.h"

class xiUDP : public xiProtoBase {
public:
	static xiUDP *      CreateOnPort( const uint16_t port );
	virtual byteLen_t	ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo = nullptr );
	virtual byteLen_t	SendBufferToAddress( const char * const buffer, const int32_t bufferLength, const addressInfo_s targetInfo );
	virtual byteLen_t	BroadcastBuffer( const char * const buffer, const int32_t bufferLength, const uint16_t port );
protected:
			xiUDP();
	virtual	~xiUDP();
};

#endif