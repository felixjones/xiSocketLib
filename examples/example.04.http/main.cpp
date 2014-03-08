#include <HyperText.h>
#include <stdio.h>

int main( int argc, char ** argv ) {
	char page[800];

	xiHTTP * const http = xiHTTP::ConnectTo( "http://www.felixjones.co.uk/" );
	while ( http ) {
		if ( http->Request( page, 800 ) ) {
			printf( "%s", page );
			break;
		}
	}

	if ( http ) {
		http->Drop();
	}

	return 1;
}