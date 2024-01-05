#ifndef DATAUPDATER_
#define DATAUPDATER_

class DataUpdater : public SequenceHolder {
public:
	int socketDescriptor;
	int clientSocket;
	int sequence_len;
	int buffer_len;
	DataUpdater(int socketDescriptor, int clientSocket, int sequence_len, int buffer_len);
	void closeConnections();
};

#endif