#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <queue>
#include <iomanip>
#include <stdlib.h>

// Handles the connection to, and reading from the socket, as well as parsing messages in the socket data.
class MessageParser
{
	public:
		int clientSocket;
		int socketDescriptor;
		int messageLength;
		int bufferLength;
		std::vector<unsigned char> buffer;
		std::vector<unsigned char> expectedHeader = {0x64, 0x82, 0x3, 0x0};
		int bufferReadPos;
		void nextReadPosition();
		void resetReadPosition();
		int receiveMessage();
		int parseMessage(short *num);
		int checkState(short num);
		int nextState();
		short nextNum();
		int checkHeader();
		int setupSocket(int* cs, int* sd);
		int initialise();

		MessageParser(int mssg_len, int num_mssg);
};

// Constructor
MessageParser::MessageParser(int mssg_len, int num_mssg){
	clientSocket = -1;
	socketDescriptor = -1;
	messageLength = mssg_len;
	bufferLength = mssg_len*num_mssg;
	std::vector<unsigned char> buf(mssg_len*num_mssg);
	buffer = buf;
	bufferReadPos = 0;
};

// Connect to the socket.
int MessageParser::initialise(){
	int sd;
    int cs;
    if (this->setupSocket(&cs, &sd) != 0){
        std::cerr << "Error Setting Up Socket" << std::endl;
        return -1;
    }
    this->clientSocket = cs;
    this->socketDescriptor = sd;
    return 0;
}

// Read data from the socket into the buffer.
int MessageParser::receiveMessage(){
	// TODO: check clientSocket > 0;
	int bytesRead = recv(clientSocket, buffer.data(), buffer.size(), 0);
	int numMessages = bytesRead / this->messageLength;
	return numMessages;
}

// Check next message in the buffer for the header and state parity.
int MessageParser::parseMessage(short *num){

	// first 4 chars are the header. We don't know much about what they mean, 
	// so just check that they are the same as we have seen previously or throw an error.
	if (this->MessageParser::checkHeader() != 0){
		std::cerr << "Header Error" << std::endl;
		return -1;
	}

	// retrieve the number from the message, and check whether it matches the state
	*num = this->MessageParser::nextNum();
	if (this->MessageParser::checkState(*num) != 0){
		std::cerr << "State Error" << std::endl;
		return -1;
	}

	// change read position for the buffer.
	this->nextReadPosition();

	return 0;
}

// Shift the read position of the buffer to the next message.
void MessageParser::nextReadPosition(){
	this->bufferReadPos+=this->messageLength;
}

// Reset the buffer read position.
void MessageParser::resetReadPosition(){
	this->bufferReadPos=0;
}

// Check the header from the message is as expected.
int MessageParser::checkHeader(){
	for (int i = 0; i < 3; i++){
		if (this->buffer[i+this->bufferReadPos] != this->expectedHeader[i]){
            std::cerr << std::hex << "Expected :" << int(this->expectedHeader[i]) << " Received: " << int(this->buffer[i+this->bufferReadPos]) << std::endl;
            return -1;
		}
	}
	return 0;
}

// Retrieve the number from the message (contained in 4th and 5th bytes in reverse order)
short MessageParser::nextNum(){
	short j;
	j = buffer[5+this->bufferReadPos];
	j <<= 8;
	j |= buffer[4+this->bufferReadPos];
	return j;
}

// Retrieve the number-state from the message (contained at the 6th byte)
int MessageParser::nextState(){
	int state = (int)buffer[6+this->bufferReadPos];
	return state;
}


// Check that the number in the message corresponds to the message state (odd, even or converged.)
int MessageParser::checkState(short num){
	int state = this->MessageParser::nextState();
	switch (state) {
	case 0:
		if (num != 1){
			std::cerr << "Warning! State is converged but number is " << num << std::endl;
			return -1;
		}
		return 0;
	case 1:
		if ((num % 2) != 1){
			std::cerr << "Warning! State is odd but number is " << num << std::endl;
			return -1;
		}
		return 0;
	case 2:
		if ((num % 2) != 0){
			std::cerr << "Warning! State is even but number is " << num << std::endl;
			return -1;
		}
		return 0;
	}
	return -1;
}

// helper function to setup the socket and connection.
int MessageParser::setupSocket(int* cs, int* sd){
    // Create a TCP socket
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketDescriptor == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Set up the server address and port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET; // addr family
    serverAddress.sin_port = htons(8080);  // Change this to your desired port
    serverAddress.sin_addr.s_addr = INADDR_ANY; // 

    // Bind the socket to the server address
    if (bind(socketDescriptor, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(socketDescriptor);
        return 1;
    }

    // Listen for incoming connections
    if (listen(socketDescriptor, SOMAXCONN) == -1) {
        std::cerr << "Failed to listen for connections" << std::endl;
        close(socketDescriptor);
        return 1;
    }

    std::cout << "Server listening on port 8080" << std::endl;

    // Accept an incoming connection
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(socketDescriptor, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength); // blocking
    if (clientSocket == -1) {
        std::cerr << "Failed to accept connection" << std::endl;
        close(socketDescriptor);
        return 1;
    }

    *cs = clientSocket;
    *sd = socketDescriptor;
    std::cout << "Client connected: " << inet_ntoa(clientAddress.sin_addr) << std::endl;
    return 0;
}
