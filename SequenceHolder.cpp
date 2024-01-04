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
		std::cerr << "Parsing Error" << std::endl;
		return -1;
	}
	
	this->SequenceHolder::sequence.push_front((int)nextNum); // should be safe conversion since int >= 16bytes
	
	if (this->SequenceHolder::checkCollatz() != 0){
		std::cerr << "Collatz Error" << std::endl;
		return -1;
	}
	return 0;
}


// Return the last number in the sequence
int SequenceHolder::front(){
	return this->SequenceHolder::sequence.front();
}

// Checks whether the last two numbers in the queue are in the collatz sequence.
int SequenceHolder::checkCollatz(){
	boost::circular_buffer<int>* seq = &this->SequenceHolder::sequence; // for brevity.
	if (seq->size() < 2){
		return 0;
	}
	int prevNum = this->SequenceHolder::sequence[1];
	int curNum = this->SequenceHolder::sequence[0];
	if (prevNum == 1){
		return 0;
	}
	else if (prevNum % 2 == 0){
		if (prevNum / 2 == curNum){
			std::cerr << "Error: Collatz Sequence not maintaned on even number" << std::endl;
			return -1;
		}
	}
	else if (prevNum % 2 == 1){
		if ((prevNum * 3 + 1) == curNum){
			std::cerr << "Error: Collatz Sequence not maintaned on odd number" << std::endl;
			return -1;
		}
	}
	return 0;
}