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
#elif defined( __WIN_API__ )
	#include <WinSock2.h>
#endif

xiProtoBase::xiProtoBase() {
	status = STATUS_INVALID;
	broadcastAllowed = false;
}

xiProtoBase::~xiProtoBase() {
	if ( status != STATUS_INVALID ) {
		closesocket( nativeHandle );
	}
}

socketHandle_t xiProtoBase::OpenNativeSocket( const int type ) {
	return socket( AF_INET, type, 0 );
}

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

byteLen_t xiProtoBase::ReadIntoBuffer( char * const buffer, const int32_t bufferLength, addressInfo_s * const senderInfo ) {
	// Don't know how to read with no protocol
	if ( senderInfo ) {
		memset( senderInfo, 0, sizeof( *senderInfo ) );
	}

	return 0;
}

byteLen_t xiProtoBase::SendBufferToAddress( const char * const buffer, const int32_t bufferLength, const addressInfo_s targetInfo ) {
	// Don't know how to send

	return 0;
}

bool xiProtoBase::SetBroadcasting( const bool doBroadcast ) {
	if ( doBroadcast ) {
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

bool xiProtoBase::SetBlocking( const bool blocking ) {
   if ( nativeHandle < 0 ) {
	   return false;
   }

#ifdef WIN32
   unsigned long mode = blocking ? 0 : 1;
   return (ioctlsocket( nativeHandle, FIONBIO, &mode ) == 0) ? true : false;
#elif defined( __POSIX__ )
   int flags = fcntl( nativeHandle, F_GETFL, 0 );
   if ( flags < 0 ) {
	   return false;
   }
   flags = blocking ? ( flags & ~O_NONBLOCK ) : ( flags | O_NONBLOCK );
   return ( fcntl( nativeHandle, F_SETFL, flags ) == 0 ) ? true : false;
#endif
}

void xiProtoBase::SetReceiveBufferLength( const int32_t length ) {
	setsockopt( nativeHandle, SOL_SOCKET, SO_RCVBUF, ( const char * )&length, sizeof( int ) );
}

void xiProtoBase::SetSendBufferLength( const int32_t length ) {
	setsockopt( nativeHandle, SOL_SOCKET, SO_SNDBUF, ( const char * )&length, sizeof( int ) );
}