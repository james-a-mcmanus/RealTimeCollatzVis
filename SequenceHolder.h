#ifndef _SequenceHolder_
#define _SequenceHolder_

#include <queue>
#include <vector>
#include <boost/circular_buffer.hpp>

class SequenceHolder: public MessageParser {
	public:
		int max_seq_len;
		//std::queue<int> sequence;
		boost::circular_buffer<int> sequence;
		SequenceHolder(int seqlen, int socket, int bytes, std::vector<unsigned char> buf);
		int checkCollatz();
		int addFromMessage();
		int front();
};

#endif