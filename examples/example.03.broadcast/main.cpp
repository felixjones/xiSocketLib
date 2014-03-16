#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define __UNSAFE__ // disable warning 4996 on VC++
#include <UDP.h>
#include <NetString.h>
#include <os.h>

#define BUFFER_LEN	( 80 )
#define BUFFER_STR	( "%79[0-9a-zA-Z.: ]s\n0" )

void CopyInputToBuffers( const char * const inputBuffer, char * const outPort, char * const outCommand );

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

	// We can create the client on any port, but with some operating systems we need to bind a port to be able to listen to it
	xiUDP * const udpSocket = xiUDP::CreateOnPort( xiSocket::PORT_ANY );
	
	if ( udpSocket ) {
		// Notify that we have successfully opened a socket
		printf( "Client started on port %u\n", udpSocket->GetPortV4() );
	}

	while ( udpSocket && isRunning ) {
		// While the socket is good and the program is running

		printf( "Enter port then command\n" );
		if ( tutorial ) {
			// Display the tutorial message
			printf( "Eg:\n27000 time\n\n" );

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
		char portSection[6];
		char command[8];
		
		// Split the input string into the buffers
		CopyInputToBuffers( buffer, &portSection[0], &command[0] );

		// Convert the port string to it's numeric value
		const uint16_t destPort = atoi( portSection );
		
		udpSocket->SetBlocking( true ); // Set the send to blocking, the program will halt until it is sent

		const byteLen_t sentBytes = udpSocket->BroadcastBuffer( command, 8, destPort ); // command is 8 chars max, see it's declaration
		if ( sentBytes > 0 ) {
			// If we managed to send something

			if ( strcmp( command, "exit" ) == 0 ) {
				// If we sent the exit command

				isRunning = false; // Stop running on the next loop
			} else {
				bool didTimeOut = true; // Presume that we won't get a reply in time
				const clock_t timeOutStart = clock(); // Record when we started listening

				do {
					udpSocket->SetBlocking( false ); // Set the socket to non-blocking so we can update the timer

					xiSocket::addressInfo_s sender;

					const byteLen_t receivedBytes = udpSocket->ReadIntoBuffer( buffer, BUFFER_LEN, &sender ); // Listen to the socket into buffer
					if ( receivedBytes > 0 ) {
						// If we received something
						char senderIPString[80];
						NetString::FromV4Address( &sender.address.protocolV4[0], IP_V4_BYTE_LEN, &senderIPString[0], 80 );

						// Output who we sent the message to and what the reply we got was
						printf( "Reply from %s:%s \"%s\"\n", senderIPString, portSection, buffer );

						didTimeOut = false; // We got a reply before the timeout
						break; // Break the listen loop
					}
				} while ( clock() < timeOutStart + 3000 ); // 3 second timeout

				if ( didTimeOut ) {
					// If we did infact timeout, notify the user
					printf( "Timed out\n" );
				}
			}
		}

		printf( "\n\n" ); // Add some padding between sessions
	}

	if ( udpSocket ) {
		// If the socket exists, Drop it (Which will destruct and close it)
		udpSocket->Drop();
	}

	return 1;
}

/*
====================
CopyInputToBuffers

	Function that takes the input string and fills some char buffers with the data
	This is a dangerous function with a high chance of crashing with bad data!
	Expects the tokens: "P C" with P the port and C the command
====================
*/
void CopyInputToBuffers( const char * const inputBuffer, char * const outPort, char * const outCommand ) {
	// Copy in IP string
	const char * c = &inputBuffer[0];
		
	// Copy in port string
	while ( *c != ' ' ) {
		const size_t offset = c - &inputBuffer[0];
		outPort[offset] = *c;
		outPort[offset + 1] = 0;

		c++;
	}
	const size_t portStrLen = strlen( outPort ) + 1;
	
	// Copy in command string
	c++;
	while ( *c != 0 ) {
		const size_t offset = c - &inputBuffer[portStrLen];
		outCommand[offset] = *c;
		outCommand[offset + 1] = 0;

		c++;
	}
}
