#include "Endian.h"

#include "os.h"

#if defined( __POSIX__ )
	#include <arpa/inet.h>
    #include <machine/endian.h>
#elif defined( __WIN_API__ )
	#include <WinSock2.h>
#endif

#if defined( __OS_X__ )
    #if __DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
        #define ntohll( x ) __DARWIN_OSSwapInt64( x )
        #define htonll( x ) ntohll( x )
    #else
        #define ntohll( x ) ( x )
        #define htonll( x ) ( x )
    #endif
#endif

int64_t Endian::NetworkToHost( const int64_t networkInt, const uint8_t length ) {
	int64_t result = 0;

	switch ( length ) {
	case 2:
		result = ntohs( ( uint16_t )networkInt );
		break;
	case 4:
		result = ntohl( ( uint32_t )networkInt );
		break;
	case 8:
		result = ntohll( networkInt );
		break;
	default:
		result = networkInt;
	}

	return result;
}

int64_t Endian::HostToNetwork( const int64_t hostInt, const uint8_t length ) {
	int64_t result = 0;

	switch ( length ) {
	case 2:
		result = htons( ( uint16_t )hostInt );
		break;
	case 4:
		result = htonl( ( uint32_t )hostInt );
		break;
	case 8:
		result = htonll( hostInt );
		break;
	default:
		result = hostInt;
	}

	return result;
}

uint64_t Endian::NetworkToHostUnsigned( const uint64_t networkInt, const uint8_t length ) {
	int64_t signedNum = *( int64_t * )&networkInt;
	signedNum = Endian::NetworkToHost( signedNum, length );

	const uint64_t result = *( int64_t * )&signedNum;

	return result;
}

uint64_t Endian::HostToNetworkUnsigned( const uint64_t hostInt, const uint8_t length ) {
	int64_t signedNum = *( int64_t * )&hostInt;
	signedNum = Endian::HostToNetwork( signedNum, length );

	const uint64_t result = *( int64_t * )&signedNum;

	return result;
}
