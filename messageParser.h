#ifndef _MessageParser_
#define _MessageParser_

class MessageParser
{
	public:
		int socketNumber;
		int messageLength;
		std::vector<unsigned char> buffer;
		std::vector<unsigned char> expectedHeader;
		//MessageParser(int s, int ml, std::vector<unsigned char> b);
		MessageParser(int socket, int bytes, std::vector<unsigned char> buf);
		int receiveMessage();
		int parseMessage();
};

#endif