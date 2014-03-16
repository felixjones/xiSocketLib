#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define __UNSAFE__ // disable warning 4996 on VC++
#include <TCP.h>
#include <NetString.h>

#define BUFFER_LEN	( 80 )
#define BUFFER_STR	( "%79[0-9a-zA-Z.: ]s\n0" )

void CopyInputToBuffers( const char * const inputBuffer, char * const outIP, char * const outPort, char * const outCommand );

/*
====================
main

	Program entry point
====================
*/
int main( int argc, char ** argv ) {
	char buffer[BUFFER_LEN]; // buffer to store the send and receive packet
	bool isRunning = true; // Set the program to running
	bool tutorial = true; // Display the tutorial

	while ( isRunning ) {
		// While the socket is good and the program is running

		printf( "Enter IP address and port then command\n" );
		if ( tutorial ) {
			// Display the tutorial message
			printf( "Eg:\n192.168.0.2:27000 time\n\n" );

			tutorial = false; // Disable the tutorial message for future runs
		}
		printf( "> " ); // Show the text input indicator
        
		const int scanState = scanf( BUFFER_STR, buffer ); // See BUFFER_STR above
		// BUFFER_STR is set to allow text, numbers, spaces and colons
		// Scanf will block while the user inputs text into buffer
		
		{ // Clear input buffer
			int ch;
			while ( ( ch = getchar() ) != EOF && ch != '\n' );
		}

		if ( scanState <= 0 ) {
			// Error with scanf
			isRunning = false; // Kill the program just in case
		}

		// Buffers for splitting the input string into
		char ipSection[16];
		char portSection[6];
		char command[8];
		
		// Split the input string into the buffers
		CopyInputToBuffers( buffer, &ipSection[0], &portSection[0], &command[0] );

		xiSocket::addressInfo_s destinationInfo; // We need to set where the packet is going

		// Convert the IP address string into a uint8_t[4] byte address for the destination
		NetString::ToV4Address( ipSection, 16, &destinationInfo.address.protocolV4[0], IP_V4_BYTE_LEN );
		// Convert the port string to it's numeric value
		destinationInfo.port = atoi( portSection );

		xiTCP * const tcpSocket = xiTCP::ConnectTo( &destinationInfo );
		if ( tcpSocket ) {
			tcpSocket->SetBlocking( true ); // Set the send to blocking, the program will halt until it is sent

			const byteLen_t sentBytes = tcpSocket->SendBuffer( command, 8 ); // command is 8 chars max, see it's declaration
			if ( sentBytes > 0 ) {
				// If we managed to send something

				if ( strcmp( command, "exit" ) == 0 ) {
					// If we sent the exit command

					isRunning = false; // Stop running on the next loop
				} else {
					bool didTimeOut = true; // Presume that we won't get a reply in time
					const clock_t timeOutStart = clock(); // Record when we started listening
					int attempts = 1;

					do {
						tcpSocket->SetBlocking( false ); // Set the socket to non-blocking so we can update the timer

						const byteLen_t receivedBytes = tcpSocket->ReadIntoBuffer( buffer, BUFFER_LEN ); // Listen to the socket into buffer
						if ( receivedBytes > 0 ) {
							// If we received something

							// Output who we sent the message to and what the reply we got was
							printf( "Reply from %s:%s \"%s\"\n", ipSection, portSection, buffer );

							didTimeOut = false; // We got a reply before the timeout
							break; // Break the listen loop
						}

						if ( clock() > timeOutStart + 5000 * attempts ) {
							attempts++;
							printf( "Still trying (Attempt %d)\n", attempts );
						}
					} while ( clock() < timeOutStart + 30000 ); // 30 second timeout

					if ( didTimeOut ) {
						// If we did infact timeout, notify the user
						printf( "Timed out\n" );
					}
				}
			}

			tcpSocket->Drop();
		} else {
			printf( "Connect failed\n" );
		}

		printf( "\n\n" ); // Add some padding between sessions
	}

	return 1;
}

/*
====================
CopyInputToBuffers

	Function that takes the input string and fills some char buffers with the data
	This is a dangerous function with a high chance of crashing with bad data!
	Expects the tokens: "X:P C" with X being the IP address, P the port and C the command
====================
*/
void CopyInputToBuffers( const char * const inputBuffer, char * const outIP, char * const outPort, char * const outCommand ) {
	// Copy in IP string
	const char * c = &inputBuffer[0];
	while ( *c != ':' ) {
		const size_t offset = c - &inputBuffer[0];
		outIP[offset] = *c;
		outIP[offset + 1] = 0;

		c++;
	}
	const size_t ipStrLen = strlen( outIP ) + 1;
		
	// Copy in port string
	c++;
	while ( *c != ' ' ) {
		const size_t offset = c - &inputBuffer[ipStrLen];
		outPort[offset] = *c;
		outPort[offset + 1] = 0;

		c++;
	}
	const size_t portStrLen = strlen( outPort ) + 1;

	const size_t ipPortLen = ( ipStrLen + portStrLen );

	// Copy in command string
	c++;
	while ( *c != 0 ) {
		const size_t offset = c - &inputBuffer[ipPortLen];
		outCommand[offset] = *c;
		outCommand[offset + 1] = 0;

		c++;
	}
}
