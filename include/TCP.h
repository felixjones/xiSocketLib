#ifndef __TCP_H__
#define __TCP_H__

#include "ProtoBase.h"

class xiTCP;

/*
================================================================================

	TCP Listen class
	This class is used for listening for incoming TCP connections
	When a connection is found with Listen() a new TCP socket will be given

================================================================================
*/
class xiTCPListen : public xiProtoBase {
public:
	static xiTCPListen *	CreateOnPort( const uint16_t port, const uint8_t protocol = PROTO_V4 );
	xiTCP *					Listen( addressInfo_s * const senderInfo = nullptr );
protected:
	static xiTCP *	CreateOnSocket( const socketHandle_t _nativeHandle, addressInfo_s * const senderInfo, const uint8_t protocol );
					xiTCPListen( const uint8_t protocol );
	virtual			~xiTCPListen();
};

/*
================================================================================

	TCP send and receive class
	This is returned by the TCP listen class' Listen() method
	Alternatively, create one of these and request it to connect to a TCP listen server

================================================================================
*/
class xiTCP : public xiProtoBase {
friend class xiTCPListen;
public:
	static xiTCP *		ConnectTo( const addressInfo_s * const listenInfo, const uint8_t protocol = PROTO_V4 );
	virtual byteLen_t	ReadIntoBuffer( char * const buffer, const int32_t bufferLength );
	virtual byteLen_t	SendBuffer( const char * const buffer, const int32_t bufferLength );
protected:
	void	Accept( const socketHandle_t _nativeHandle, addressInfo_s * const senderInfo );
	bool	Connect( const addressInfo_s * const listenInfo );
			xiTCP( const uint8_t protocol );
	virtual	~xiTCP();
};

#endif