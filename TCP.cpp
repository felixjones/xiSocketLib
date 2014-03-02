#include "TCP.h"

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

#ifndef SOCKET_ERROR
    #define SOCKET_ERROR    ( -1 )
#endif

#ifdef __WIN_API__
typedef int socklen_t;
#endif

xiTCPListen * xiTCPListen::CreateOnPort( const uint16_t port ) {
	xiTCPListen * const self = new xiTCPListen();

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

xiTCPListen::xiTCPListen() {
	status = STATUS_NOT_BOUND;
	nativeHandle = OpenNativeSocket( SOCK_STREAM );

	if ( nativeHandle == INVALID_SOCKET ) {
		status = STATUS_INVALID;
	}
}

xiTCPListen::~xiTCPListen() {
	
}

xiTCP * xiTCPListen::Listen() {
	const int listenStatus = listen( nativeHandle, 1 );
	if ( !listenStatus ) {
		// worked, open connection
		xiTCP * const newConnection = CreateOnSocket( nativeHandle );

		return newConnection;
	} else {
		status = STATUS_ERROR;
	}

	return nullptr;
}

xiTCP * xiTCP::ConnectTo( const addressInfo_s listenInfo ) {
	xiTCP * const self = new xiTCP();

	self->nativeHandle = OpenNativeSocket( SOCK_STREAM );
	if ( self->nativeHandle == INVALID_SOCKET ) {
		self->status = STATUS_INVALID;
	}

	if ( self->status == STATUS_INVALID ) {
		delete( self );

		return nullptr;
	}

	if ( !self->BindToPortV4( 0 ) ) {
		delete( self );

		return nullptr;
	}

	const bool isConnected = self->Connect( listenInfo );
	if ( !isConnected ) {
		delete( self );

		return nullptr;
	}

	self->Grab();

	return self;
}

xiTCP * xiTCPListen::CreateOnSocket( const socketHandle_t _nativeHandle ) {
	xiTCP * const self = new xiTCP();
	self->Accept( _nativeHandle );

	if ( self->status == STATUS_INVALID ) {
		delete( self );

		return nullptr;
	}
	
	self->Grab();

	return self;
}

void xiTCP::Accept( const socketHandle_t _nativeHandle ) {
	nativeHandle = accept( _nativeHandle, nullptr, nullptr );

	if ( nativeHandle == INVALID_SOCKET ) {
		status = STATUS_INVALID;
	}
}

bool xiTCP::Connect( const addressInfo_s listenInfo ) {
	sockaddr_in target;
	int targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
#ifdef __WIN_API__
	target.sin_family = AF_INET;
	target.sin_addr.S_un.S_un_b.s_b1 = listenInfo.address.protocolV4[0];
	target.sin_addr.S_un.S_un_b.s_b2 = listenInfo.address.protocolV4[1];
	target.sin_addr.S_un.S_un_b.s_b3 = listenInfo.address.protocolV4[2];
	target.sin_addr.S_un.S_un_b.s_b4 = listenInfo.address.protocolV4[3];
#else
    memcpy( &target.sin_addr.s_addr, &listenInfo.address.protocolV4[0], sizeof( target.sin_addr.s_addr ) );
#endif
	
	target.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( listenInfo.port, sizeof( listenInfo.port ) );

	const int connectResult = connect( nativeHandle, ( sockaddr * )&target, targetLength );
	if ( connectResult == SOCKET_ERROR ) {
		return false;
	}

	return true;
}

byteLen_t xiTCP::ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo ) {
	return recv( nativeHandle, buffer, bufferLength, 0 );
}

byteLen_t xiTCP::SendBuffer( const char * const buffer, const int32_t bufferLength ) {
	return send( nativeHandle, buffer, bufferLength, 0 );
}

xiTCP::xiTCP() {
	status = STATUS_NOT_BOUND;
}

xiTCP::~xiTCP() {

}