#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <iomanip>
#include <stdlib.h>

class MessageParser
{
	public:
		int socketNumber;
		int messageLength;
		std::vector<unsigned char> buffer;
		std::vector<unsigned char> expectedHeader = {64, 82, 3, 0};

		int receiveMessage();
		int parseMessage();
		MessageParser(int s, int b, std::vector<unsigned char> buf);
};

MessageParser::MessageParser(int s, int b, std::vector<unsigned char> buf){
	socketNumber = s;
	messageLength = b;
	buffer = buf;
};

int MessageParser::receiveMessage(){
	int bytesRead = recv(socketNumber, buffer.data(), buffer.size(), 0);
	return bytesRead;
}

int MessageParser::parseMessage(){
	// first 4 chars are the header. We don't know much about what they mean, 
	// so just check that they are the same as we have seen previously or throw an error.
	std::vector<unsigned char> headerMessage(buffer.begin(), buffer.begin()+4);
	if (headerMessage != expectedHeader){
		std::cerr << "Header received unexpected" << std::endl;
	}

	// construct the hexnum from the 5th and 6th numbers in the data.
    std::string hexNum = "0x";
    hexNum.append(1, buffer[5]);
    hexNum.append(1, buffer[6]);
    char * p;
    long nextSequence = strtol(hexNum.c_str(), &p, 16);
    if (*p != 0){
    	std::cerr << "Couldn't parse data as hexadecimal" << std::endl;
    }

	// 6th char is the first part of the hex number
	// 5th char is the second part.
	// 7th char is the state (converged, odd, or even respectively)

    return nextSequence;
}