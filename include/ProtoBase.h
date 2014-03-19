#ifndef __PROTO_BASE_H__
#define __PROTO_BASE_H__

#include "Socket.h"

/*
================================================================================

	Base class for Protocols
	Both UDP and TCP inherit this class

================================================================================
*/
class xiProtoBase : protected xiSocket {
public:
	bool		SetBlocking( const bool blocking );
	void		SetReceiveBufferLength( const int32_t length );
	void		SetSendBufferLength( const int32_t length );
	uint16_t	GetPort() const;

	xiRefCounter::Grab;
	xiRefCounter::Drop;
protected:
                            xiProtoBase( const uint8_t protocol );
	virtual                 ~xiProtoBase();
	static socketHandle_t	OpenNativeSocket( const int type );
	bool					SetBroadcasting( const bool doBroadcast );
	bool                    BindToPortV4( const uint16_t port );
	bool                    BindToPortV6( const uint16_t port );

	bool			broadcastAllowed;
	const uint8_t	protocolVer;
};

#endif