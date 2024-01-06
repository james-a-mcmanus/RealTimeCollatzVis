#include <string>
#include <queue>
#include <iostream>
#include "messageParser.h"
#include <boost/circular_buffer.hpp>

// Holds the sequence of numbers read out from the message parser.
class SequenceHolder: public MessageParser {

	public:
		boost::circular_buffer<double> sequence;
		int max_seq_len;
		int addFromMessage();
		int front();
		int checkCollatz();
		SequenceHolder(int seqlen, int mssg_len, int num_mssg);
		boost::circular_buffer<double>::const_reverse_iterator begin();
		boost::circular_buffer<double>::const_reverse_iterator end();
		int size();
};

// Constructor
SequenceHolder::SequenceHolder(int seqlen, int mssg_len, int num_mssg) : MessageParser(mssg_len, num_mssg){
	max_seq_len = seqlen;
	sequence.set_capacity(seqlen);
};

// Add the numbers from the message buffer into the sequence.
int SequenceHolder::addFromMessage(){

	short nextNum;
	int numMessages = this->receiveMessage();

	for (int i=0; i < numMessages; i++){
		
		if (this->SequenceHolder::parseMessage(&nextNum) != 0){
			std::cerr << "Parsing Error" << std::endl;
			return -1;
		}
		this->SequenceHolder::sequence.push_front(static_cast<double>(nextNum));
		
		if (this->SequenceHolder::checkCollatz() != 0){
			std::cerr << "Collatz Error" << std::endl;
			return -1;
		}
	}
	this->resetReadPosition();
	return 0;
}

// Return the last number in the sequence
int SequenceHolder::front(){
	return this->SequenceHolder::sequence.front();
}

// Iterator for the beginning of the circular buffer sequence
boost::circular_buffer<double>::const_reverse_iterator SequenceHolder::begin(){
	return this->SequenceHolder::sequence.rbegin();
}

// Iterator for the end of the circular buffer sequence
boost::circular_buffer<double>::const_reverse_iterator SequenceHolder::end(){
	return this->SequenceHolder::sequence.rend();
}

// Size of the circular buffer sequence.
int SequenceHolder::size(){
	return this->SequenceHolder::sequence.size();
}

// Checks whether the last two numbers in the queue are in the collatz sequence.
int SequenceHolder::checkCollatz(){
	
	boost::circular_buffer<double>* seq = &this->SequenceHolder::sequence; // for brevity.
	if (seq->size() < 2){
		return 0;
	}

	int prevNum = this->SequenceHolder::sequence[1];
	int curNum = this->SequenceHolder::sequence[0];

	// don't check if previously converged.
	if (prevNum == 1){
		return 0;
	}
	else if (prevNum % 2 == 0){
		if ((prevNum / 2) != curNum){
			std::cerr << "Error: Collatz Sequence not maintaned on even number" << std::endl;
			return -1;
		}
	}
	else if (prevNum % 2 == 1){
		if ((prevNum * 3 + 1) != curNum){
			std::cerr << "Error: Collatz Sequence not maintaned on odd number" << std::endl;
			return -1;
		}
	}
	return 0;
}