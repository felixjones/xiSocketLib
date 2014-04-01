#xiSocketLib#

C++ Unix/Winsock wrapper library

## Usage ##

UDP Create Example
	
	#include <UDP.h>
	
	// Create UDP socket (Will automatically bind to any IPv4 port
	xiUDP * const udpSocket = xiUDP::CreateOnPort( 12345, xiSocket::PROTO_V4 );
	if ( udpSocket ) {
		// Socket is created on port 12345 successfully
	}

UDP Listen Example

	char receivedBytes[500]; // Where the received bytes go
	const int maxLength = 500; // How many bytes we can accept
	xiSocket::addressInfo_s sender; // Info to store who sent the bytes

	const int receivedLen = udpSocket->ReadIntoBuffer( &receivedBytes[0], maxLength, &sender );
	if ( receivedLen > -1 ) {
		// receivedBytes contains what we received
		// receivedLen tells us how many bytes we have
		// sender now contains info on who sent the packet
	}

UDP Send Example

	const char * const myPacket = "Hello World"; // Message to send
	const int packetLen = strlen( myPacket ) + 1; // Length of message (Plus null term, just in case)

	xiSocket::addressInfo_s destination; // Packet destination
	xiSocket::AddressV4( 192, 168, 0, 2, 12345, &destination ); // Set destination IPv4 address and port to 192.168.0.2:12345

	const int sentBytes = udpSocket->SendBufferToAddress( &myPacket[0], packetLen, &destination );
	if ( sentBytes > -1 ) {
		// Packet sent, hopefully it reaches the destination
	}
