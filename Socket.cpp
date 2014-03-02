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
#endif

xiSocket::xiSocket() {
	nativeHandle = 0; // This is a null socket, it shouldn't do anything

#ifdef __WIN_API__
	if ( winsockReferenceCount++ == 0 ) {
		WSAStartup( MAKEWORD( 2, 2 ), &winSockData ); // Start winsock
	}
#endif
}

xiSocket::~xiSocket() {
#ifdef __WIN_API__
	if ( --winsockReferenceCount == 0 ) {
		WSACleanup(); // Destroy winsock
	}
#endif
}

byteLen_t xiSocket::ReadInt8( const char * const buffer, void * const varptr ) {
	memcpy( varptr, buffer, sizeof( uint8_t ) );

	return sizeof( uint8_t );
}

byteLen_t xiSocket::ReadInt16( const char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint16_t );

	uint16_t num = *( uint16_t * )buffer;
	num = Endian::NetworkToHostUnsigned( num, size );

	memcpy( varptr, &num, size );

	return size;
}

byteLen_t xiSocket::ReadInt32( const char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint32_t );

	uint32_t num = *( uint32_t * )buffer;
	num = Endian::NetworkToHostUnsigned( num, size );

	memcpy( varptr, &num, size );

	return size;
}

byteLen_t xiSocket::ReadInt64( const char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint64_t );

	uint64_t num = *( uint64_t * )buffer;
	num = Endian::NetworkToHostUnsigned( num, size );

	memcpy( varptr, &num, size );

	return size;
}

byteLen_t xiSocket::WriteInt8( char * const buffer, void * const varptr ) {
	memcpy( buffer, varptr, sizeof( uint8_t ) );

	return sizeof( uint8_t );
}

byteLen_t xiSocket::WriteInt16( char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint16_t );

	uint16_t num = *( uint16_t * )varptr;
	num = Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}

byteLen_t xiSocket::WriteInt32( char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint32_t );

	uint32_t num = *( uint32_t * )varptr;
	num = Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}

byteLen_t xiSocket::WriteInt64( char * const buffer, void * const varptr ) {
	const byteLen_t size = sizeof( uint64_t );

	uint64_t num = *( uint64_t * )varptr;
	num = Endian::HostToNetworkUnsigned( num, size );

	memcpy( buffer, &num, size );

	return size;
}
