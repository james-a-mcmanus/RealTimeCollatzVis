#ifndef SEQUENCEHOLDER_
#define SEQUENCEHOLDER_

#include <queue>
#include <vector>
#include <boost/circular_buffer.hpp>

class SequenceHolder: public MessageParser {
	public:
		int max_seq_len;
		//std::queue<int> sequence;
		boost::circular_buffer<int> sequence;
		SequenceHolder(int seqlen, int socket, int buf_len);
		int checkCollatz();
		int addFromMessage();
		int front();
};

#endif