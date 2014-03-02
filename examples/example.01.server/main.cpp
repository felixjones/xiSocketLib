#include <string.h>
#include <time.h>
#include <stdio.h>

#include <UDP.h>
#include <NetString.h>

#define BUFFER_LEN	( 500 )
#define SERVER_PORT	( 27000 )

/*
====================
main

	Program entry point
====================
*/
int main( int argc, char ** argv ) {
	char buffer[BUFFER_LEN]; // Out buffer for receiving and sending packets
	bool isRunning = true; // Flag that keeps the while loop running

	xiUDP * const udpSocket = xiUDP::CreateOnPort( SERVER_PORT ); // Open socket on port SERVER_PORT
	// udpSocket->SetBlocking( false ); // Optional, set to non-blocking

	if ( udpSocket ) {
		// Print that the socket has successfully opened
		printf( "Server started on port %u\n", SERVER_PORT );
	}

	while ( udpSocket && isRunning ) {
		// While the socket is valid and the server is still running

		xiSocket::addressInfo_s senderInfo; // We store the sender info here

		// Read from the socket
		const byteLen_t receivedBytes = udpSocket->ReadIntoBuffer( &buffer[0], BUFFER_LEN, &senderInfo );
		if ( receivedBytes > 0 ) {
			// If we received anything ( receivedBytes > 0 )
			// The buffer contains the packet

			char senderIPString[80]; // Place to store the string version of the sender IP

			// Convert sender IP to string
			const size_t ipStringLen = NetString::FromV4Address( &senderInfo.address.protocolV4[0], 4, &senderIPString[0], 80 );
			sprintf( &senderIPString[ipStringLen], ":%u", senderInfo.port ); // Append the port to the end of the string

			if ( strcmp( buffer, "exit" ) == 0 ) {
				// If the buffer says "exit"
				printf( "Exit request received from %s\n", senderIPString );

				isRunning = false; // Set the server to no-longer running
			} else if ( strcmp( buffer, "time" ) == 0 ) {
				// If the buffer says "time"
				printf( "Time request received from %s\n", senderIPString );

				const time_t timeNow = time( 0 ); // Get the current time
				tm timeStruct;
				timeStruct = *localtime( &timeNow ); // Get the time as a structure

				const int timeHour = timeStruct.tm_hour; // Convert time to hours
				const int timeMinute = timeStruct.tm_min; // Convert time to minutes

				sprintf( &buffer[0], "%d:%d\0", timeHour, timeMinute ); // Build a string of the time into the buffer

				// Attempt to send the buffer back to the same IP address and port that sent the packet
				const byteLen_t sentBytes = udpSocket->SendBufferToAddress( &buffer[0], strlen( buffer ) + 1, senderInfo );
				if ( sentBytes > 0 ) {
					// If the sending was successful, output it (This does not mean they got the packet)
					printf( "Replied with \"%s\"\n", buffer );
				}
			}
		}
	}

	if ( udpSocket ) {
		// If our socket is still open, call Drop (Which will deconstruct the socket)
		udpSocket->Drop();
	}

	return 1;
}