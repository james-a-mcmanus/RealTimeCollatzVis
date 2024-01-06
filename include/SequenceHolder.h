#ifndef SEQUENCEHOLDER_
#define SEQUENCEHOLDER_

#include <queue>
#include <vector>
#include <boost/circular_buffer.hpp>

class SequenceHolder: public MessageParser {
	public:
		int max_seq_len;
		boost::circular_buffer<double> sequence;
		SequenceHolder(int seqlen, int mssg_len, int num_mssg);
		int checkCollatz();
		int addFromMessage();
		int front(); // get from the front
		boost::circular_buffer<double>::const_reverse_iterator begin();
		boost::circular_buffer<double>::const_reverse_iterator end();
		int size();
};

#endif