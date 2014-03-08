#define __UNSAFE__
#include "Socket.h"

#include <stdio.h>
#include "os.h"
#include "Endian.h"

#if defined( __WIN_API__ )
    #pragma comment( lib, "Ws2_32.lib" )

    #include <WinSock2.h>
	#include <WS2tcpip.h>

    namespace WinSock {
        uint32_t	winsockReferenceCount = 0;
        WSADATA		winSockData;
    }

    using namespace WinSock;
#elif defined( __POSIX__ )
    #include <string.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
#endif

const uint16_t	xiSocket::PORT_ANY = 0;

/*
====================
xiSocket::xiSocket

	Constructor
	If winsock is in use, the Winsock system is started up here
====================
*/
xiSocket::xiSocket() {
	nativeHandle = 0; // This is a null socket, it shouldn't do anything

#if defined( __WIN_API__ )
	if ( winsockReferenceCount++ == 0 ) {
		const int winSockError = WSAStartup( MAKEWORD( 2, 2 ), &winSockData ); // Start winsock
		if ( winSockError ) {
			if ( --winsockReferenceCount == 0 ) {
				WSACleanup(); // Destroy winsock
			}

			status = STATUS_ERROR;
		}
	}
#endif
}

/*
====================
xiSocket::~xiSocket

	Deconstructor
	If winsock is in use, the reference count of Winsock is decremented
	When the reference hits 0, winsock is stopped
====================
*/
xiSocket::~xiSocket() {
#if defined( __WIN_API__ )
	if ( --winsockReferenceCount == 0 ) {
		WSACleanup(); // Destroy winsock
	}
#endif
}

/*
====================
xiSocket::ReadInt8

	Function for reading a byte from a given buffer
	The byte is stored in varptr
====================
*/
byteLen_t xiSocket::ReadInt8( const char * const buffer, void * const varptr ) {
	memcpy( varptr, buffer, sizeof( uint8_t ) );

	return sizeof( uint8_t );
}

/*
====================
xiSocket::ReadInt16

	Function for reading 2 bytes from a given buffer
	The bytes are stored in varptr
====================
*/
byteLen_t xiSocket::ReadInt16( const char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint16_t );

	uint16_t num = *( uint16_t * )buffer;
	num = ( uint16_t )Endian::NetworkToHostUnsigned( num, size );

	memcpy( varptr, &num, size );

	return size;
}

/*
====================
xiSocket::ReadInt32

	Function for reading 4 bytes from a given buffer
	The bytes are stored in varptr
====================
*/
byteLen_t xiSocket::ReadInt32( const char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint32_t );

	uint32_t num = *( uint32_t * )buffer;
	num = ( uint32_t )Endian::NetworkToHostUnsigned( num, size );

	memcpy( varptr, &num, size );

	return size;
}

/*
====================
xiSocket::ReadInt64

	Function for reading 8 bytes from a given buffer
	The bytes are stored in varptr
====================
*/
byteLen_t xiSocket::ReadInt64( const char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint64_t );

	uint64_t num = *( uint64_t * )buffer;
	num = Endian::NetworkToHostUnsigned( num, size );

	memcpy( varptr, &num, size );

	return size;
}

/*
====================
xiSocket::WriteInt8

	Writes 1 byte of varptr into the buffer
====================
*/
byteLen_t xiSocket::WriteInt8( char * const buffer, const void * const varptr ) {
	memcpy( buffer, varptr, sizeof( uint8_t ) );

	return sizeof( uint8_t );
}

/*
====================
xiSocket::WriteInt16

	Writes 2 bytes of varptr into the buffer
====================
*/
byteLen_t xiSocket::WriteInt16( char * const buffer, const void * const varptr ) {
	const byteLen_t size = sizeof( uint16_t );

	uint16_t num = *( uint16_t * )varptr;
	num = ( uint16_t )Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}

/*
====================
xiSocket::WriteInt32

	Writes 4 bytes of varptr into the buffer
====================
*/
byteLen_t xiSocket::WriteInt32( char * const buffer, const void * const varptr ) {
	const byteLen_t size = sizeof( uint32_t );

	uint32_t num = *( uint32_t * )varptr;
	num = ( uint32_t )Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}

/*
====================
xiSocket::WriteInt64

	Writes 8 bytes of varptr into the buffer
====================
*/
byteLen_t xiSocket::WriteInt64( char * const buffer, const void * const varptr ) {
	const byteLen_t size = sizeof( uint64_t );

	uint64_t num = *( uint64_t * )varptr;
	num = Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}

/*
====================
xiSocket::ReadBytes

	Reads byteLen number of bytes from buffer into byteptr
====================
*/
byteLen_t xiSocket::ReadBytes( const char * const buffer, uint8_t * const byteptr, const byteLen_t byteLen ) {
	memcpy( &byteptr[0], &buffer[0], ( size_t )byteLen );

	return byteLen;
}

/*
====================
xiSocket::WriteBytes

	Writes byteLen number of bytes from byteptr into buffer
====================
*/
byteLen_t xiSocket::WriteBytes( char * const buffer, const uint8_t * const byteptr, const byteLen_t byteLen ) {
	memcpy( &buffer[0], &byteptr[0], ( size_t )byteLen );

	return byteLen;
}

/*
====================
xiSocket::ReadString

	Copies buffer into byteptr up to a null-terminator
====================
*/
byteLen_t xiSocket::ReadString( const char * const buffer, char * const byteptr ) {
	const char * c = &buffer[0];
	while ( *c ) {
		c++;
	}
	const size_t strLen = ( c - &buffer[0] );

	memcpy( &byteptr[0], &buffer[0], strLen );
	const byteLen_t lenPlusNull = ( byteLen_t )strlen( buffer ) + 1; // Returns the string plus the null terminator

	return lenPlusNull;
}

/*
====================
xiSocket::WriteString

	Copies byteptr into buffer up to a null-terminator
====================
*/
byteLen_t xiSocket::WriteString( char * const buffer, const char * const byteptr ) {
	const char * c = &buffer[0];
	while ( *c ) {
		c++;
	}
	const size_t strLen = ( c - &buffer[0] );

	memcpy( &buffer[0], &byteptr[0], strLen );
	const byteLen_t lenPlusNull = ( byteLen_t )strlen( byteptr ) + 1; // Returns the string plus the null terminator

	return lenPlusNull;
}

/*
====================
xiSocket::DomainLookup

	Takes a url as a string and performs DNS to return the address information
	URL is in the format a://b.c.d:p/d.i
	a : optional protocol
	b : optional www
	c : domain
	d : extension
	p : optional port
	d : ignored filepath
	i : ignored file extension
====================
*/
bool xiSocket::DomainLookup( const char * const url, const uint16_t port, xiSocket::addressInfo_s * const info ) {
#if defined( __WIN_API__ )
	xiSocket openSocket; // We do this to kick off WinSock if it hasn't yet started
#endif
	char portStr[10];
	sprintf( portStr, "%u", port );

    memset( info, 0, sizeof( *info ) );
	info->port = 80;

    addrinfo hints;
    memset( &hints, 0, sizeof( hints ) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
	
    // Perform DNS lookup
	addrinfo * res = nullptr;
    const int addInfoState = getaddrinfo( url, portStr, &hints, &res );

    if ( addInfoState != 0 ) {
		return false;
	}

	for ( addrinfo * ptr = res; ptr != nullptr; ptr = ptr->ai_next ) {
		if ( ptr->ai_family == AF_INET ) {
			const sockaddr_in * const sockData = ( const sockaddr_in * )ptr->ai_addr; // Set current address
#if defined( __WIN_API__ )
            info->address.protocolV4[0] = sockData->sin_addr.S_un.S_un_b.s_b1;
            info->address.protocolV4[1] = sockData->sin_addr.S_un.S_un_b.s_b2;
            info->address.protocolV4[2] = sockData->sin_addr.S_un.S_un_b.s_b3;
            info->address.protocolV4[3] = sockData->sin_addr.S_un.S_un_b.s_b4;
#elif defined( __POSIX__ )
            memcpy( &info->address.protocolV4[0], &sockData->sin_addr.s_addr, sizeof( sockData->sin_addr.s_addr ) );
#endif
			break; // Escape the linked list crawl
		}
	}
    
    freeaddrinfo( res );
	
	return true;
}