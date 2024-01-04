#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <iomanip>
#include <stdlib.h>

enum STATE {CONVERGED, ODD, EVEN};

class MessageParser
{
	public:
		int socketNumber;
		int messageLength;
		std::vector<unsigned char> buffer;
		std::vector<unsigned char> expectedHeader = {64, 82, 3, 0};

		int receiveMessage();
		int parseMessage(short *num);
		int checkState(short num);
		int nextState();
		short nextNum();
		int checkHeader();

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

	return 0;

	// std::vector<unsigned char> headerMessage(buffer.begin(), buffer.begin()+8);
	// if (headerMessage != expectedHeader){
	// 	//std::cerr << "Header received unexpected" << std::endl;
	// 	for (auto const& c : headerMessage)
	// 		std::cout << std::hex << (int)c << ' ';
	// 	std::cout << std::endl;
	// }

	// 6th char is the first part of the hex number
	// 5th char is the second part.
	// 7th char is the state (converged, odd, or even respectively)

    // return nextSequence;
}

// TODO: Check the header from the message
int MessageParser::checkHeader(){
	return 0;
}

// Retrieve the number from the message
short MessageParser::nextNum(){
	short j;
	j = buffer[5];
	j <<= 8;
	j |= buffer[4];
	return j;
}

// Retrieve the number-state from the message
int MessageParser::nextState(){
	int state = (int)buffer[6];
	return state;
}


// Check that the number in the message corresponds to the message state (odd, even or converged.)
int MessageParser::checkState(short num){
	int state = this->MessageParser::nextState();
	std::cout << "checking number: " << num << " Having state " << state << std::endl;
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