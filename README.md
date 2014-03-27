#xiSocketLib#

C++ Unix/Winsock wrapper library

## Usage ##

UDP Create Example
	
	#include <UDP.h>
	
	// Create UDP socket (Will automatically bind to any IPv4 port
	xiUDP * const udpSocket = xiUDP::CreateOnPort( 12345 );
	if ( udpSocket ) {
		// Socket is created on port 12345 successfully
	}

UDP Listen Example

	char destination[800]; // Where the received bytes go
	const int maxLength = 800; // How many bytes we can accept
	xiSocket::addressInfo_s sender; // Info to store who sent the bytes

	const int receivedBytes = udpSocket->ReadIntoBuffer( &destination[0], maxLength, &sender );
	if ( receivedBytes > 0 ) {
		// destination contains what we received
		// receivedBytes tells us how many bytes we have
		// sender now contains info on who sent the packet
	}

UDP Send Example

	const char * const myPacket = "Hello World"; // Message to send
	const int packetLen = strlen( myPacket ) + 1; // Length of message (Plus null term, just in case)

	xiSocket::addressInfo_s destination; // Packet destination
	xiSocket::AddressV4( 192, 168, 0, 2, 12345, &destination ); // Set destination IPv4 address and port to 192.168.0.2:12345

	const int sentBytes = udpSocket->SendBufferToAddress( &myPacket[0], packetLen, &destination );
	if ( sentBytes > 0 ) {
		// Packet sent, hopefully it reaches the destination
	}
