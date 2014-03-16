#include "UDP.h"

#include "os.h"
#include "Endian.h"

#if defined( __POSIX__ )
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <string.h>
#elif defined( __WIN_API__ )
	#include <WinSock2.h>
#endif

#if defined( __OS_X__ )
	#define INVALID_SOCKET  ( -1 )
#endif

#if defined( __WIN_API__ )
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
xiUDP * xiUDP::CreateOnPort( const uint16_t port ) {
	xiUDP * const self = new xiUDP();

	if ( self->status == STATUS_INVALID ) {
		delete( self );

		return nullptr;
	}

	if ( !self->BindToPortV4( port ) ) {
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
xiUDP::xiUDP() {
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
	sockaddr_in sender;
	socklen_t senderLength = ( socklen_t )sizeof( sender );
    
	const byteLen_t receivedBytes = recvfrom( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&sender, &senderLength );

	if ( senderInfo ) {
		memset( senderInfo, 0, sizeof( *senderInfo ) );
        
#if defined( __WIN_API__ )
		senderInfo->address.protocolV4[0] = sender.sin_addr.S_un.S_un_b.s_b1;
		senderInfo->address.protocolV4[1] = sender.sin_addr.S_un.S_un_b.s_b2;
		senderInfo->address.protocolV4[2] = sender.sin_addr.S_un.S_un_b.s_b3;
		senderInfo->address.protocolV4[3] = sender.sin_addr.S_un.S_un_b.s_b4;
#elif defined( __POSIX__ )
        memcpy( &senderInfo->address.protocolV4[0], &sender.sin_addr.s_addr, sizeof( sender.sin_addr.s_addr ) );
#endif

		senderInfo->port = ( uint16_t )Endian::NetworkToHostUnsigned( sender.sin_port, sizeof( sender.sin_port ) );
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

	sockaddr_in target;
	int targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
#if defined( __WIN_API__ )
	target.sin_family = AF_INET;
	target.sin_addr.S_un.S_un_b.s_b1 = targetInfo->address.protocolV4[0];
	target.sin_addr.S_un.S_un_b.s_b2 = targetInfo->address.protocolV4[1];
	target.sin_addr.S_un.S_un_b.s_b3 = targetInfo->address.protocolV4[2];
	target.sin_addr.S_un.S_un_b.s_b4 = targetInfo->address.protocolV4[3];
#elif defined( __POSIX__ )
    memcpy( &target.sin_addr.s_addr, &targetInfo->address.protocolV4[0], sizeof( target.sin_addr.s_addr ) );
#endif

	target.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( targetInfo->port, sizeof( targetInfo->port ) );

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
	
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = INADDR_BROADCAST;

	target.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( port, sizeof( port ) );

	const byteLen_t sentBytes = sendto( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&target, targetLength );

	return sentBytes;
}
