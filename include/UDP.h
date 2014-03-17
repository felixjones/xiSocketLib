#ifndef __UDP_H__
#define __UDP_H__

#include "ProtoBase.h"

/*
================================================================================

	UDP sendto and receivefrom
	This class must be constructed with a port
	It will open the port for listening or sending
	If it cannot open the port, a nullptr is returned and the memory is deallocated

================================================================================
*/
class xiUDP : public xiProtoBase {
public:
	static xiUDP *      CreateOnPort( const uint16_t port, const uint8_t protocol = PROTO_V4 );
	virtual byteLen_t	ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo = nullptr );
	virtual byteLen_t	SendBufferToAddress( const char * const buffer, const int32_t bufferLength, const addressInfo_s * const targetInfo );
	virtual byteLen_t	BroadcastBuffer( const char * const buffer, const int32_t bufferLength, const uint16_t port );
protected:
			xiUDP( const uint8_t protocol );
	virtual	~xiUDP();
};

#endif