#include "UDP.h"

#include "os.h"
#include "Endian.h"

#if defined( __POSIX__ )
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <string.h>

	#if !defined( INVALID_SOCKET )
		#define INVALID_SOCKET  ( -1 )
	#endif
#elif defined( __WIN_API__ )
	#include <WS2tcpip.h>

	typedef int socklen_t;
#endif
	
/*
====================
xiUDP::CreateOnPort

	Open a UDP socket on a given port
	This constructs the memory too
	If it fails, a nullptr is returned
	The port is automatically bound, so it is ready for both send and receive
====================
*/
xiUDP * xiUDP::CreateOnPort( const uint16_t port, const uint8_t protocol ) {
	xiUDP * const self = new xiUDP( protocol );

	if ( self->status == STATUS_INVALID ) {
		delete( self );

		return nullptr;
	}

	if ( protocol == PROTO_V4 ) {
		if ( !self->BindToPortV4( port ) ) {
			delete( self );

			return nullptr;
		}
	} else if ( protocol == PROTO_V6 ) {
		if ( !self->BindToPortV6( port ) ) {
			delete( self );

			return nullptr;
		}
	} else {
		delete( self );

		return nullptr;
	}

	self->Grab();

	return self;
}

/*
====================
xiUDP::xiUDP

	Constructor
	Opens up a UDP socket
	Called internally
====================
*/
xiUDP::xiUDP( const uint8_t protocol ) : xiProtoBase( protocol ) {
	status = STATUS_NOT_BOUND;
	nativeHandle = OpenNativeSocket( SOCK_DGRAM );

	if ( nativeHandle == INVALID_SOCKET ) {
		status = STATUS_INVALID;
	}
}

/*
====================
xiUDP::~xiUDP

	Deconstructor
	Protobase does the important destruction
====================
*/
xiUDP::~xiUDP() {
}

/*
====================
xiUDP::ReadIntoBuffer

	Read from the UDP socket into a given buffer
	senderInfo is not required, but would be needed for replying
	Returns the length of the received packet
====================
*/
byteLen_t xiUDP::ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo ) {
	union {
		sockaddr_in		v4;
		sockaddr_in6	v6;
	} sender;

	socklen_t senderLength = ( socklen_t )sizeof( sender );
	const byteLen_t receivedBytes = recvfrom( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&sender, &senderLength );

	if ( senderInfo ) {
		memset( senderInfo, 0, sizeof( *senderInfo ) );
        
		if ( protocolVer == PROTO_V4 ) {
#if defined( __WIN_API__ )
			senderInfo->address.protocolV4[0] = sender.v4.sin_addr.S_un.S_un_b.s_b1;
			senderInfo->address.protocolV4[1] = sender.v4.sin_addr.S_un.S_un_b.s_b2;
			senderInfo->address.protocolV4[2] = sender.v4.sin_addr.S_un.S_un_b.s_b3;
			senderInfo->address.protocolV4[3] = sender.v4.sin_addr.S_un.S_un_b.s_b4;
#elif defined( __POSIX__ )
			memcpy( &senderInfo->address.protocolV4[0], &sender.v4.sin_addr.s_addr, sizeof( sender.v4.sin_addr.s_addr ) );
#endif
			senderInfo->port = ( uint16_t )Endian::NetworkToHostUnsigned( sender.v4.sin_port, sizeof( sender.v4.sin_port ) );
		} else if ( protocolVer == PROTO_V6 ) {
#if defined( __WIN_API__ )
			memcpy( &senderInfo->address.protocolV6[0], &sender.v6.sin6_addr.u.Byte[0], sizeof( sender.v6.sin6_addr.u ) );
			senderInfo->port = ( uint16_t )Endian::NetworkToHostUnsigned( sender.v6.sin6_port, sizeof( sender.v6.sin6_port ) );
#elif defined( __POSIX__ )
			memcpy( &senderInfo->address.protocolV6[0], &sender.v6.sin6_addr, sizeof( sender.v6.sin6_addr ) );
#endif
		}
	}

	return receivedBytes;
}

/*
====================
xiUDP::SendBufferToAddress

	Fire-and-forget
	Sends a given buffer to the destination of targetInfo
	Nothing is done to check if it gets there
====================
*/
byteLen_t xiUDP::SendBufferToAddress( const char * const buffer, const int32_t bufferLength, const addressInfo_s * const targetInfo ) {
	if ( SetBroadcasting( false ) == false ) {
		return -1; // Could not disable broadcasting
	}

	union {
		sockaddr_in		v4;
		sockaddr_in6	v6;
	} target;
	int targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
	if ( protocolVer == PROTO_V4 ) {
#if defined( __WIN_API__ )
		target.v4.sin_family = AF_INET;
		target.v4.sin_addr.S_un.S_un_b.s_b1 = targetInfo->address.protocolV4[0];
		target.v4.sin_addr.S_un.S_un_b.s_b2 = targetInfo->address.protocolV4[1];
		target.v4.sin_addr.S_un.S_un_b.s_b3 = targetInfo->address.protocolV4[2];
		target.v4.sin_addr.S_un.S_un_b.s_b4 = targetInfo->address.protocolV4[3];
#elif defined( __POSIX__ )
		memcpy( &target.v4.sin_addr.s_addr, &targetInfo->address.protocolV4[0], sizeof( target.v4.sin_addr.s_addr ) );
#endif
		target.v4.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( targetInfo->port, sizeof( targetInfo->port ) );
	} else if ( protocolVer == PROTO_V6 ) {
#if defined( __WIN_API__ )
		memcpy( &target.v6.sin6_addr.u.Byte[0], &targetInfo->address.protocolV6[0], sizeof( target.v6.sin6_addr.u ) );
		target.v6.sin6_port = ( uint16_t )Endian::HostToNetworkUnsigned( targetInfo->port, sizeof( targetInfo->port ) );
#elif defined( __POSIX__ )
		memcpy( &target.v6.sin6_addr, &targetInfo->address.protocolV6[0], sizeof( target.v6.sin6_addr ) );
#endif
	}

	const byteLen_t sentBytes = sendto( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&target, targetLength );

	return sentBytes;
}

/*
====================
xiUDP::BroadcastBuffer

	Broadcasts a given buffer on the same subnet that the socket is bound
	The port is the "destination" port of all the potential receivers of the packet
	The broadcastAllowed boolean must be set for this method to work
====================
*/
byteLen_t xiUDP::BroadcastBuffer( const char * const buffer, const int32_t bufferLength, const uint16_t port ) {
	if ( SetBroadcasting( true ) == false ) {
		return -1; // Could not enable broadcasting
	}

	sockaddr_in target;
	int targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
	if ( protocolVer == PROTO_V4 ) {
		target.sin_family = AF_INET;
	} else if ( protocolVer == PROTO_V6 ) {
		target.sin_family = AF_INET6;
	} else {
		return -1;
	}

    target.sin_addr.s_addr = INADDR_BROADCAST;

	target.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( port, sizeof( port ) );

	const byteLen_t sentBytes = sendto( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&target, targetLength );

	return sentBytes;
}
