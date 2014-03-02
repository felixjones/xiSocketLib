#ifndef __ENDIAN_H__
#define __ENDIAN_H__

#include <stdint.h>

namespace Endian {
	int64_t		NetworkToHost( const int64_t networkInt, const uint8_t length );
	int64_t		HostToNetwork( const int64_t hostInt, const uint8_t length );
	uint64_t	NetworkToHostUnsigned( const uint64_t networkInt, const uint8_t length );
	uint64_t	HostToNetworkUnsigned( const uint64_t hostInt, const uint8_t length );
}

#endif