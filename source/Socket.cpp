#include "Socket.h"

#include "os.h"
#include "Endian.h"

#ifdef __WIN_API__
    #pragma comment( lib, "Ws2_32.lib" )

    #include <WinSock2.h>

    namespace WinSock {
        uint32_t	winsockReferenceCount = 0;
        WSADATA		winSockData;
    }

    using namespace WinSock;
#elif defined( __POSIX__ )
    #include <string.h>
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

#ifdef __WIN_API__
	if ( winsockReferenceCount++ == 0 ) {
		WSAStartup( MAKEWORD( 2, 2 ), &winSockData ); // Start winsock
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
#ifdef __WIN_API__
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
	num = ( uint16_t )Endian::NetworkToHostUnsigned( num, size );

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
byteLen_t xiSocket::WriteInt8( char * const buffer, void * const varptr ) {
	memcpy( buffer, varptr, sizeof( uint8_t ) );

	return sizeof( uint8_t );
}

/*
====================
xiSocket::WriteInt16

	Writes 2 bytes of varptr into the buffer
====================
*/
byteLen_t xiSocket::WriteInt16( char * const buffer, void * const varptr ) {
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
byteLen_t xiSocket::WriteInt32( char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint32_t );

	uint32_t num = *( uint32_t * )varptr;
	num = ( uint16_t )Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}

/*
====================
xiSocket::WriteInt64

	Writes 8 bytes of varptr into the buffer
====================
*/
byteLen_t xiSocket::WriteInt64( char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint64_t );

	uint64_t num = *( uint64_t * )varptr;
	num = Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}
