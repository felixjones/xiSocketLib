#include "TCP.h"

#include "os.h"
#include "Endian.h"

#if defined( __POSIX__ )
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <string.h>

	#if !defined( SOCKET_ERROR )
		#define SOCKET_ERROR    ( -1 )
	#endif

	#if !defined( INVALID_SOCKET )
		#define INVALID_SOCKET  ( -1 )
	#endif
#elif defined( __WIN_API__ )
	#include <WS2tcpip.h>

	typedef int socklen_t;
#endif

/*
====================
xiTCPListen::CreateOnPort

	Allocates memory and constructs a TCP listen server socket
	If it fails, the memory is cleaned up and a nullptr returned
====================
*/
xiTCPListen * xiTCPListen::CreateOnPort( const uint16_t port, const uint8_t protocol ) {
	xiTCPListen * const self = new xiTCPListen( protocol );

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
xiTCPListen::xiTCPListen

	Protected constructor
	This is called internally
	Starts a native TCP socket
====================
*/
xiTCPListen::xiTCPListen( const uint8_t protocol ) : xiProtoBase( protocol ) {
	status = STATUS_NOT_BOUND;
	nativeHandle = OpenNativeSocket( SOCK_STREAM );

	if ( nativeHandle == INVALID_SOCKET ) {
		status = STATUS_INVALID;
	}
}

/*
====================
xiTCPListen::~xiTCPListen

	Protected destructor
	The parent Protobase class does the important destruction
====================
*/
xiTCPListen::~xiTCPListen() {
}

/*
====================
xiTCPListen::Listen

	Listens for incoming TCP connections
	Returns a new xiTCP socket for communicating on new connections
====================
*/
xiTCP * xiTCPListen::Listen( addressInfo_s * const senderInfo ) {
	const int listenStatus = listen( nativeHandle, 1 );
	if ( !listenStatus ) {
		// worked, open connection
		xiTCP * const newConnection = CreateOnSocket( nativeHandle, senderInfo, protocolVer );

		return newConnection;
	} else {
		status = STATUS_ERROR;
	}

	return nullptr;
}

/*
====================
xiTCPListen::CreateOnSocket

	Internally used to construct the listen socket
	The native handle is given to the method, as opposed to created by the method
====================
*/
xiTCP * xiTCPListen::CreateOnSocket( const socketHandle_t _nativeHandle, addressInfo_s * const senderInfo, const uint8_t protocol ) {
	xiTCP * const self = new xiTCP( protocol );
	self->Accept( _nativeHandle, senderInfo );

	if ( self->status == STATUS_INVALID ) {
		delete( self );

		return nullptr;
	}
	
	self->Grab();

	return self;
}

/*
====================
xiTCP::ConnectTo

	Use this to create a TCP socket for connecting with a TCP listen server
	The address information of the server is needed for the connection
	It will attempt the connection and only return a valid pointer if the connection is successful
====================
*/
xiTCP * xiTCP::ConnectTo( const addressInfo_s * const listenInfo, const uint8_t protocol ) {
	xiTCP * const self = new xiTCP( protocol );

	self->nativeHandle = OpenNativeSocket( SOCK_STREAM );
	if ( self->nativeHandle == INVALID_SOCKET ) {
		self->status = STATUS_INVALID;
	}

	if ( self->status == STATUS_INVALID ) {
		delete( self );

		return nullptr;
	}

	if ( protocol == PROTO_V4 ) {
		if ( !self->BindToPortV4( 0 ) ) {
			delete( self );

			return nullptr;
		}
	} else if ( protocol == PROTO_V6 ) {
		if ( !self->BindToPortV6( 0 ) ) {
			delete( self );

			return nullptr;
		}
	} else {
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

/*
====================
xiTCP::Accept

	Used internally when a xiTCP socket is created by a listen server
	This method is "accepts" the socket as being bound by the listen socket
====================
*/
void xiTCP::Accept( const socketHandle_t _nativeHandle, addressInfo_s * const senderInfo ) {
	sockaddr_in target;
	socklen_t targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
	nativeHandle = accept( _nativeHandle, ( sockaddr * )&target, &targetLength );

	if ( nativeHandle == INVALID_SOCKET ) {
		status = STATUS_INVALID;
	} else {
#if defined( __WIN_API__ )
		senderInfo->address.protocolV4[0] = target.sin_addr.S_un.S_un_b.s_b1;
		senderInfo->address.protocolV4[1] = target.sin_addr.S_un.S_un_b.s_b2;
		senderInfo->address.protocolV4[2] = target.sin_addr.S_un.S_un_b.s_b3;
		senderInfo->address.protocolV4[3] = target.sin_addr.S_un.S_un_b.s_b4;
#elif defined( __POSIX__ )
        memcpy( &senderInfo->address.protocolV4[0], &target.sin_addr.s_addr, sizeof( target.sin_addr.s_addr ) );
#endif

		senderInfo->port = ( uint16_t )Endian::NetworkToHostUnsigned( target.sin_port, sizeof( target.sin_port ) );
	}
}

/*
====================
xiTCP::Connect

	Used internally to start the client to server connection
====================
*/
bool xiTCP::Connect( const addressInfo_s * const listenInfo ) {
	sockaddr_in target;
	int targetLength = ( int )sizeof( target );
	memset( &target, 0, sizeof( target ) );
	
#if defined( __WIN_API__ )
	target.sin_family = AF_INET;
	target.sin_addr.S_un.S_un_b.s_b1 = listenInfo->address.protocolV4[0];
	target.sin_addr.S_un.S_un_b.s_b2 = listenInfo->address.protocolV4[1];
	target.sin_addr.S_un.S_un_b.s_b3 = listenInfo->address.protocolV4[2];
	target.sin_addr.S_un.S_un_b.s_b4 = listenInfo->address.protocolV4[3];
#elif defined( __POSIX__ )
    memcpy( &target.sin_addr.s_addr, &listenInfo->address.protocolV4[0], sizeof( target.sin_addr.s_addr ) );
#endif
	
	target.sin_port = ( uint16_t )Endian::HostToNetworkUnsigned( listenInfo->port, sizeof( listenInfo->port ) );

	const int connectResult = connect( nativeHandle, ( sockaddr * )&target, targetLength );
	if ( connectResult == SOCKET_ERROR ) {
		return false;
	}

	return true;
}

/*
====================
xiTCP::ReadIntoBuffer

	Calls the operating system's recv function to read from the TCP connection
====================
*/
byteLen_t xiTCP::ReadIntoBuffer( char * const buffer, const int32_t bufferLength ) {
	return recv( nativeHandle, buffer, bufferLength, 0 );
}

/*
====================
xiTCP::SendBuffer

	Calls the operating system's send function to send a buffer down the connection
====================
*/
byteLen_t xiTCP::SendBuffer( const char * const buffer, const int32_t bufferLength ) {
	return send( nativeHandle, buffer, bufferLength, 0 );
}

/*
====================
xiTCP::xiTCP

	Constructor
	Defaults a TCP connection as not bound
====================
*/
xiTCP::xiTCP( const uint8_t protocol ) : xiProtoBase( protocol ) {
	status = STATUS_NOT_BOUND;
}

/*
====================
xiTCP::~xiTCP

	Deconstructor
	Protobase does the important destruction
====================
*/
xiTCP::~xiTCP() {
}
