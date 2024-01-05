#ifndef _MessageParser_
#define _MessageParser_

class MessageParser
{
	public:
		int clientSocket;
		int socketDescriptor;
		int messageLength;
		std::vector<unsigned char> buffer;
		std::vector<unsigned char> expectedHeader;
		MessageParser(int buf_len);
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