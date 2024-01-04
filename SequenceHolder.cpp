#include <string>
#include <queue>
#include <iostream>
#include "messageParser.h"
#include <boost/circular_buffer.hpp>

class SequenceHolder: public MessageParser {

	public:
		//std::queue<int> sequence;
		boost::circular_buffer<int> sequence;
		int max_seq_len;
		int addFromMessage();
		int front();
		int checkCollatz();
		SequenceHolder(int seqlen, int socket, int bytes, std::vector<unsigned char> buf);
};

// Constructor
SequenceHolder::SequenceHolder(int seqlen, int socket, int bytes, std::vector<unsigned char> buf) : MessageParser(socket, bytes, buf){
	max_seq_len = seqlen;
	sequence.set_capacity(seqlen);
};

// Add the number from the message buffer into the sequence.
int SequenceHolder::addFromMessage(){

	short nextNum;
	if (this->SequenceHolder::parseMessage(&nextNum) != 0){
		std::cerr << "" << std::endl;
		return -1;
	}
	this->SequenceHolder::sequence.push_front((int)nextNum); // should be safe conversion since int >= 16bytes
	this->SequenceHolder::checkCollatz();
	return -1;
}


// Return the last number in the sequence
int SequenceHolder::front(){
	return this->SequenceHolder::sequence.front();
}

// Return the penultimate number in the sequence
// int SequenceHolder::penultimate(){
// 	return this->SequenceHolder::sequence.();
// }

// Checks whether the last two numbers in the queue are in the collatz sequence.
int SequenceHolder::checkCollatz(){
	boost::circular_buffer<int>* seq = &this->SequenceHolder::sequence; // for brevity.
	if (seq->size() < 2){
		return 0;
	}
	std::cout << this->SequenceHolder::sequence[seq->size()-1] << std::endl;
	return 0;
}