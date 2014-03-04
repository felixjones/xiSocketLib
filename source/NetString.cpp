#include "NetString.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "os.h"

#define IP_V4_SEGMENTS	( 4 )

using namespace NetString;

namespace NetString {
	void	CopySection( char input[5], size_t charIndex, const char * const buffer, const size_t bufferLen );
}

/*
====================
NetString::CopySection

	Copies a piece of the IP string into the input buffer
	Will always stop at the next '.' it finds
	So you can copy 192.168.0.1 section by section
====================
*/
void NetString::CopySection( char input[5], size_t charIndex, const char * const buffer, const size_t bufferLen ) {
	const size_t charA = ( charIndex + IP_V4_SEGMENTS - 3 );
	const size_t charB = ( charIndex + IP_V4_SEGMENTS - 2 );
	const size_t charC = ( charIndex + IP_V4_SEGMENTS - 1 );
	const size_t charD = ( charIndex + IP_V4_SEGMENTS );

	if ( charA < bufferLen && buffer[charA] != '.' ) {
		input[0] = buffer[charA];
	} else {
		input[0] = 0;
	}
	if ( charB < bufferLen && buffer[charB] != '.' ) {
		input[1] = buffer[charB];
	} else {
		input[1] = 0;
	}
	if ( charC < bufferLen && buffer[charC] != '.' ) {
		input[2] = buffer[charC];
	} else {
		input[2] = 0;
	}
	if ( charD < bufferLen && buffer[charD] != '.' ) {
		input[3] = buffer[charD];
	} else {
		input[3] = 0;
	}
	input[4] = 0; // Null terminate
}

/*
====================
NetString::ToV4Address

	Converts a human readable IPv4 string to the byte values
	Requires a uint8_t buffer of size 4 bytes to store the result
====================
*/
size_t NetString::ToV4Address( const char * const buffer, const size_t bufferLen, uint8_t * const output, const size_t outputLen ) {
	if ( outputLen < IP_V4_SEGMENTS || !output ) {
		// Needs 32 bit output!
		return 0;
	} else if ( !bufferLen || !buffer ) {
		// Needs an input buffer
		return 0;
	}

	size_t count = 0;
	uint8_t * byte = &output[3];

	size_t charIndex = bufferLen - 1;
	do {
		if ( buffer[charIndex] == '.' || charIndex == 0 ) {
			// Found byte point!
			char input[5];
			CopySection( input, ( charIndex ? charIndex : -1 ), buffer, bufferLen );
			
			*byte = atoi( input );
			byte--;
			
			count++;
		}
	} while ( charIndex-- );

	return count;
}

/*
====================
NetString::FromV4Address

	Converts a 4 byte IPv4 address to a character string
	The string is stored in the output buffer
====================
*/
size_t NetString::FromV4Address( const uint8_t * const buffer, const size_t bufferLen, char * const output, const size_t outputLen ) {
	if ( outputLen < 16 || !output ) {
		// IP 4 Addresses are a minimum of 16 chars in length!
		return 0;
	} else if ( bufferLen < IP_V4_SEGMENTS || !buffer ) {
		// Needs an IP address to work!
		return 0;
	}

#if defined( __WIN_API__ )
	#pragma warning( push)
	#pragma warning( disable: 4996 )
#endif
	sprintf( output, "%u.%u.%u.%u", buffer[0], buffer[1], buffer[2], buffer[3] );
#if defined( __WIN_API__ )
	#pragma warning( pop )
#endif

	return strlen( output );
}