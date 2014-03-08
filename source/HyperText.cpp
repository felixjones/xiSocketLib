#include "HyperText.h"

#include <stdio.h>
#include "os.h"

#if defined( __POSIX__ )
	#include <arpa/inet.h>
	#include <sys/socket.h>

	#if !defined( SOCKET_ERROR )
		#define SOCKET_ERROR    ( -1 )
	#endif
#elif defined( __WIN_API__ )
	#include <WinSock2.h>
#endif

xiHTTP * xiHTTP::ConnectTo( const char * const url, const uint16_t port ) {
	addressInfo_s info;
	
	char urlStr[80];
	memcpy( &urlStr[0], url, strlen( url ) + 1 );

	const char * const protocol = strstr( url, "://" );
	if ( protocol ) {
		intptr_t offset = ( intptr_t )( protocol + 3 - url );

		int ii = 0;
		do {
			urlStr[ii] = urlStr[ii + offset ];
			if ( urlStr[ii] == '/' ) {
				break;
			}
		} while ( ii++, urlStr[ii + offset] );
		urlStr[ii] = 0;
	}

	const bool foundDomain = xiSocket::DomainLookup( urlStr, port, &info );
	if ( !foundDomain ) {
		return nullptr;
	}

	xiHTTP * const self = new xiHTTP( urlStr );
	
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

	const bool connected = self->Connect( &info );
	if ( !connected ) {
		delete( self );

		return nullptr;
	}

	self->Grab();

	return self;
}

bool xiHTTP::Request( char * const buffer, const byteLen_t bufferLen ) {
	char getString[80];
	sprintf( getString, "GET /index.html HTTP/1.1\nHost: %s", urlStr );

	const byteLen_t sentBytes = SendBuffer( getString, strlen( getString ) );
	if ( sentBytes > 0 ) {
		
		SetBlocking( false );
		const byteLen_t receivedBytes = ReadIntoBuffer( buffer, bufferLen );
		SetBlocking( true );
		if ( receivedBytes > 0 ) {
			return true;
		}
	}

	return false;
}

xiHTTP::xiHTTP( const char * const host ) {
	memcpy( urlStr, host, strlen( host ) + 1 );
}