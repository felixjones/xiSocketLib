#ifndef __HYPER_TEXT_H__
#define __HYPER_TEXT_H__

#include "TCP.h"

class xiHTTP : public xiTCP {
public:
	static xiHTTP *	ConnectTo( const char * const url, const uint16_t port = 80 );
	bool			Request( char * const buffer, const byteLen_t bufferLen );
protected:
	xiHTTP( const char * const host );
private:
	char	urlStr[80];
};

#endif