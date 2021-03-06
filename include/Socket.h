#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "SmartPointer.h"
#include "os.h"

#if defined( __WIN_API__ )
	typedef uintptr_t   socketHandle_t;
    typedef int         byteLen_t;
    typedef int         socketLen_t;
#elif defined( __POSIX__ )
	typedef int         socketHandle_t;
	typedef long        byteLen_t;
    typedef uint32_t    socketLen_t;
#endif

#define IP_V4_BYTE_LEN	( 4 )
#define IP_V6_BYTE_LEN	( 16 )

/*
================================================================================

	Base socket class
	Contains functions for reading and writing integers until a buffer
	Also has the structure for address information

================================================================================
*/
class xiSocket : public virtual xiRefCounter {
public:
	enum status_e {
		STATUS_INVALID		=	0x0,
		STATUS_NOT_BOUND	=	0x1,
		STATUS_BOUND		=	0x2,
		STATUS_ERROR		=	0x3
	};

	struct addressInfo_s {
		union address_u {
			uint8_t	protocolV4[IP_V4_BYTE_LEN];
			uint8_t	protocolV6[IP_V6_BYTE_LEN];
		} address;

		uint16_t	port;
	};

						xiSocket();
	virtual				~xiSocket();
	static byteLen_t	ReadInt8( const char * const buffer, void * const varptr );
	static byteLen_t	ReadInt16( const char * const buffer, void * const varptr );
	static byteLen_t	ReadInt32( const char * const buffer, void * const varptr );
	static byteLen_t	ReadInt64( const char * const buffer, void * const varptr );
	static byteLen_t	ReadBytes( const char * const buffer, void * const byteptr, const byteLen_t byteLen );
	static byteLen_t	ReadString( const char * const buffer, char * const byteptr );
	static byteLen_t	WriteInt8( char * const buffer, const void * const varptr );
	static byteLen_t	WriteInt16( char * const buffer, const void * const varptr );
	static byteLen_t	WriteInt32( char * const buffer, const void * const varptr );
	static byteLen_t	WriteInt64( char * const buffer, const void * const varptr );
	static byteLen_t	WriteBytes( char * const buffer, const void * const byteptr, const byteLen_t byteLen );
	static byteLen_t	WriteString( char * const buffer, const char * const byteptr );
	static bool			DomainLookupV4( const char * const url, const uint16_t port, xiSocket::addressInfo_s * const info );
	static bool			DomainLookupV6( const char * const url, const uint16_t port, xiSocket::addressInfo_s * const info );
	static bool			AddressV4( const uint8_t bA, const uint8_t bB, const uint8_t bC, const uint8_t bD, const uint16_t port, xiSocket::addressInfo_s * const info );
	static bool			AddressFromStringV4( const char * const address, xiSocket::addressInfo_s * const info );

	static const uint16_t	PORT_ANY;
	static const uint8_t	PROTO_V4;
	static const uint8_t	PROTO_V6;
protected:
	status_e		status;
	socketHandle_t	nativeHandle;
};

#endif