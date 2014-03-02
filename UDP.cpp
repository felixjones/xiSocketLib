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

#ifdef __WIN_API__
typedef int socklen_t;
#endif

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

xiUDP::xiUDP() {
	status = STATUS_NOT_BOUND;
	nativeHandle = OpenNativeSocket( SOCK_DGRAM );

	if ( nativeHandle == INVALID_SOCKET ) {
		status = STATUS_INVALID;
	}
}

xiUDP::~xiUDP() {
	
}

byteLen_t xiUDP::ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo ) {
	sockaddr_in sender;
	socklen_t senderLength = ( socklen_t )sizeof( sender );
    
	const byteLen_t receivedBytes = recvfrom( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&sender, &senderLength );

	if ( senderInfo ) {
		memset( senderInfo, 0, sizeof( *senderInfo ) );
        
#ifdef __WIN_API__
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

byteLen_t xiUDP::SendBufferToAddress( const char * const buffer, const int32_t bufferLength, const addressInfo_s targetInfo ) {
	sockaddr_in target;
	int targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
#ifdef __WIN_API__
	target.sin_family = AF_INET;
	target.sin_addr.S_un.S_un_b.s_b1 = targetInfo.address.protocolV4[0];
	target.sin_addr.S_un.S_un_b.s_b2 = targetInfo.address.protocolV4[1];
	target.sin_addr.S_un.S_un_b.s_b3 = targetInfo.address.protocolV4[2];
	target.sin_addr.S_un.S_un_b.s_b4 = targetInfo.address.protocolV4[3];
#elif defined( __POSIX__ )
    memcpy( &target.sin_addr.s_addr, &targetInfo.address.protocolV4[0], sizeof( target.sin_addr.s_addr ) );
#endif

	target.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( targetInfo.port, sizeof( targetInfo.port ) );

	const byteLen_t sentBytes = sendto( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&target, targetLength );

	return sentBytes;
}

byteLen_t xiUDP::BroadcastBuffer( const char * const buffer, const int32_t bufferLength, const uint16_t port ) {
	if ( broadcastAllowed == false ) {
		// Broadcasting not allowed!
		return 0;
	}

	sockaddr_in target;
	int targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
#ifdef __WIN_API__
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = INADDR_BROADCAST;
#elif defined( __POSIX__ )
    //memcpy( &target.sin_addr.s_addr, &targetInfo.address.protocolV4[0], sizeof( target.sin_addr.s_addr ) );
#endif

	target.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( port, sizeof( port ) );

	const byteLen_t sentBytes = sendto( nativeHandle, buffer, bufferLength, 0, ( sockaddr * )&target, targetLength );

	return sentBytes;
}