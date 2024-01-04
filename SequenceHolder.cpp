#include <string>
#include <queue>
#include <iostream>
#include "messageParser.h"

class SequenceHolder: public MessageParser {

	public:
		std::queue<int> sequence;
		int max_seq_len;
		int addFromMessage();
		int back();
		SequenceHolder(int seqlen, int socket, int bytes, std::vector<unsigned char> buf);
};

SequenceHolder::SequenceHolder(int seqlen, int socket, int bytes, std::vector<unsigned char> buf) : MessageParser(socket, bytes, buf){
	max_seq_len = seqlen;
};


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

int SequenceHolder::back(){
	return this->SequenceHolder::sequence.back();
}