#ifndef __PROTO_BASE_H__
#define __PROTO_BASE_H__

#include "Socket.h"

/*
================================================================================

	Base class for Protocols
	Both UDP and TCP inherit this class

================================================================================
*/
class xiProtoBase : public xiSocket {
public:
	bool		SetBlocking( const bool blocking );
	bool		SetBroadcasting( const bool doBroadcast );
	void		SetReceiveBufferLength( const int32_t length );
	void		SetSendBufferLength( const int32_t length );
	uint16_t	GetPort() const;
protected:
                            xiProtoBase();
	virtual                 ~xiProtoBase();
	static socketHandle_t	OpenNativeSocket( const int type );
	bool                    BindToPortV4( const uint16_t port );
	virtual byteLen_t       ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo = nullptr );
	virtual byteLen_t       SendBufferToAddress( const char * const buffer, const int32_t bufferLength, const addressInfo_s targetInfo );

	status_e	status;
	bool		broadcastAllowed;
};

#endif