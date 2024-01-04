#include <string>
#include <queue>
#include <iostream>
#include "messageParser.h"
#include <boost/circular_buffer.hpp>

class SequenceHolder: public MessageParser {

	public:
		std::queue<int> sequence;
		int max_seq_len;
		int addFromMessage();
		int back();
		int checkCollatz();
		SequenceHolder(int seqlen, int socket, int bytes, std::vector<unsigned char> buf);
};

// Constructor
SequenceHolder::SequenceHolder(int seqlen, int socket, int bytes, std::vector<unsigned char> buf) : MessageParser(socket, bytes, buf){
	max_seq_len = seqlen;
};

// Add the number from the message buffer into the sequence.
int SequenceHolder::addFromMessage(){

	short nextNum;
	if (this->SequenceHolder::parseMessage(&nextNum) != 0){
		std::cerr << "" << std::endl;
		return -1;
	}
	if (this->SequenceHolder::sequence.size() > this->SequenceHolder::max_seq_len){
		this->SequenceHolder::sequence.pop();
	}
	this->SequenceHolder::sequence.push(nextNum); // should be safe conversion since int >= 16bytes
	return -1;
}


// Return the last number in the sequence
int SequenceHolder::back(){
	return this->SequenceHolder::sequence.back();
}

// Return the penultimate number in the sequence
// int SequenceHolder::penultimate(){
// 	return this->SequenceHolder::sequence.();
// }

// Checks whether the last two numbers in the queue are in the collatz sequence.
int SequenceHolder::checkCollatz(){
	if (this->SequenceHolder::sequence.size() < 2){
		return 0;
	}
	//this->SequenceHolder::sequence()
	return 0;
}