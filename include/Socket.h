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

/*
================================================================================

	Base socket class
	Contains functions for reading and writing integers until a buffer
	Also has the structure for address information

================================================================================
*/
class xiSocket : public virtual xiRefCounter {
public:
						xiSocket();
	virtual				~xiSocket();
	static byteLen_t	ReadInt8( const char * const buffer, void * const varptr );
	static byteLen_t	ReadInt16( const char * const buffer, void * const varptr );
	static byteLen_t	ReadInt32( const char * const buffer, void * const varptr );
	static byteLen_t	ReadInt64( const char * const buffer, void * const varptr );
	static byteLen_t	WriteInt8( char * const buffer, void * const varptr );
	static byteLen_t	WriteInt16( char * const buffer, void * const varptr );
	static byteLen_t	WriteInt32( char * const buffer, void * const varptr );
	static byteLen_t	WriteInt64( char * const buffer, void * const varptr );
	
	enum status_e {
		STATUS_INVALID		=	0x0,
		STATUS_NOT_BOUND	=	0x1,
		STATUS_BOUND		=	0x2,
		STATUS_ERROR		=	0x3
	};

	struct addressInfo_s {
		union address_u {
			uint8_t	protocolV4[4];
		} address;

		uint16_t	port;
	};

	static const uint16_t	PORT_ANY;
protected:
	socketHandle_t	nativeHandle;
};

#endif