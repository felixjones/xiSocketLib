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
	static xiTCPListen *	CreateOnPort( const uint16_t port );
	xiTCP *					Listen();
protected:
	static xiTCP *	CreateOnSocket( const socketHandle_t _nativeHandle );
					xiTCPListen();
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
	static xiTCP *		ConnectTo( const addressInfo_s listenInfo );
	virtual byteLen_t	ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo = nullptr );
	virtual byteLen_t	SendBuffer( const char * const buffer, const int32_t bufferLength );
protected:
	void	Accept( const socketHandle_t _nativeHandle );
	bool	Connect( const addressInfo_s listenInfo );
			xiTCP();
	virtual	~xiTCP();
};

#endif