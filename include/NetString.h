#ifndef __NET_STRING_H__
#define __NET_STRING_H__

#include <stddef.h>
#include <stdint.h>

/*
================================================================================

	Functions for converting from byte array IP addresses to human readable strings
	Note: There is currently (As of this writing) not standard way of writing v6 addresses
	IPv6 support will come in the future

================================================================================
*/
namespace NetString {
	size_t	ToV4Address( const char * const buffer, const size_t bufferLen, uint8_t * const output, const size_t outputLen );
	size_t	FromV4Address( const uint8_t * const buffer, const size_t bufferLen, char * const output, const size_t outputLen );
}

#endif