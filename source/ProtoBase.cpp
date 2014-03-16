#include "ProtoBase.h"

#include "os.h"
#include "Endian.h"

#if defined( __POSIX__ )
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <string.h>

	#define closesocket( x )    close( x )

	#if !defined( SOCKET_ERROR )
		#define SOCKET_ERROR    ( -1 )
	#endif
#elif defined( __WIN_API__ )
	#include <WinSock2.h>
#endif

/*
====================
xiProtoBase::xiProtoBase

	Constructor
	Defaults the socket as invalid
	Disables UDP broadcasting by default
====================
*/
xiProtoBase::xiProtoBase() {
	status = STATUS_INVALID;
	broadcastAllowed = false;
}

/*
====================
xiProtoBase::~xiProtoBase

	Deconstructor
	Will only close a socket that it believes is valid
====================
*/
xiProtoBase::~xiProtoBase() {
	if ( status != STATUS_INVALID ) {
		closesocket( nativeHandle );
	}
}

/*
====================
xiProtoBase::OpenNativeSocket

	Returns a new socket by the operating system
	This should be used internally once for each socket
====================
*/
socketHandle_t xiProtoBase::OpenNativeSocket( const int type ) {
	return socket( AF_INET, type, 0 );
}

/*
====================
xiProtoBase::BindToPortV4

	Calls the operating system's bind-to-any
====================
*/
bool xiProtoBase::BindToPortV4( const uint16_t port ) {
	sockaddr_in socketInfo;
	memset( &socketInfo, 0, sizeof( socketInfo ) );

	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = ( uint16_t )Endian::HostToNetwork( port, sizeof( port ) );
	socketInfo.sin_addr.s_addr = INADDR_ANY;

	if ( bind( nativeHandle, ( sockaddr * )&socketInfo, sizeof( socketInfo ) ) == -1 ) {
		return false; // Failed
	}

	status = STATUS_BOUND;
	return true;
}

/*
====================
xiProtoBase::SetBroadcasting

	Sets if broadcasting is allowed by the protocol
	Only works for UDP
====================
*/
bool xiProtoBase::SetBroadcasting( const bool doBroadcast ) {
	if ( broadcastAllowed == doBroadcast ) {
		// This broadcast option is already set
		return true;
	} else if ( doBroadcast ) {
		int val = 1;
		const int optStatus = setsockopt( nativeHandle, SOL_SOCKET, SO_BROADCAST, ( char * )&val, sizeof( int ) );
		if ( optStatus != SOCKET_ERROR ) {
			broadcastAllowed = doBroadcast;
		} else {
			return false;
		}
	} else {
		int val = 0;
		const int optStatus = setsockopt( nativeHandle, SOL_SOCKET, SO_BROADCAST, ( char * )&val, sizeof( int ) );
		if ( optStatus != SOCKET_ERROR ) {
			broadcastAllowed = doBroadcast;
		} else {
			return false;
		}
	}

	return true;
}

/*
====================
xiProtoBase::SetBlocking

	Sets if the socket input/output blocks calls
	This will stop lock-ups with the send/receive calls
====================
*/
bool xiProtoBase::SetBlocking( const bool blocking ) {
   if ( nativeHandle == 0 ) {
	   return false;
   }

#if defined( __WIN_API__ )
   unsigned long mode = blocking ? 0 : 1;
   return ( ioctlsocket( nativeHandle, FIONBIO, &mode ) == 0) ? true : false;
#elif defined( __POSIX__ )
   int flags = fcntl( nativeHandle, F_GETFL, 0 );
   if ( flags < 0 ) {
	   return false;
   }
   flags = blocking ? ( flags & ~O_NONBLOCK ) : ( flags | O_NONBLOCK );
   return ( fcntl( nativeHandle, F_SETFL, flags ) == 0 ) ? true : false;
#endif
}

/*
====================
xiProtoBase::SetReceiveBufferLength

	Sets the length of the operating system's receive buffer
	This is how many packets are built up in the system before sent to the application
	If you were to set this to zero, the application must receive fast enough to get all packets
	Recommended to set this to just above the maximum size of a single packet if you want to remove receive delay
====================
*/
void xiProtoBase::SetReceiveBufferLength( const int32_t length ) {
	setsockopt( nativeHandle, SOL_SOCKET, SO_RCVBUF, ( const char * )&length, sizeof( int ) );
}

/*
====================
xiProtoBase::SetSendBufferLength

	Sets the length of the operating system's send buffer
	This is how many packets are built up in the system before they are sent to the network
	If you were to set this to zero, the application must not send too many packets at once otherwise some will be dropped
	Recommended to set this to just above the maximum size of a single packet if you want to remove sending delay
====================
*/
void xiProtoBase::SetSendBufferLength( const int32_t length ) {
	setsockopt( nativeHandle, SOL_SOCKET, SO_SNDBUF, ( const char * )&length, sizeof( int ) );
}

/*
====================
xiProtoBase::GetPortV4

	Returns the bound port of this socket
====================
*/
uint16_t xiProtoBase::GetPortV4() const {
	sockaddr_in addressInfo;
	socketLen_t infoLen = sizeof( addressInfo );
	if ( getsockname( nativeHandle, ( sockaddr * )&addressInfo, &infoLen ) != -1 ) {
		return ( uint16_t )Endian::NetworkToHost( addressInfo.sin_port, sizeof( addressInfo.sin_port ) );
	}
	
	return 0;
}
