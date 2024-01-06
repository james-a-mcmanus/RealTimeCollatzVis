#ifndef _MessageParser_
#define _MessageParser_

#include <vector>

class MessageParser
{
	public:
		int clientSocket;
		int socketDescriptor;
		int messageLength;
		int bufferLength;
		std::vector<unsigned char> buffer;
		std::vector<unsigned char> expectedHeader;
		int bufferReadPos;
		void nextReadPosition();
		void resetReadPosition();		
		MessageParser(int mssg_len, int num_mssg);
		int receiveMessage();
		int parseMessage(short *num);
		int checkState(short num);
		int nextState();
		short nextNum();
		int checkHeader();
		int setupSocket(int* cs, int* sd);
		int initialise();
};

int setupSocket(int* cs, int* sd);

#endif