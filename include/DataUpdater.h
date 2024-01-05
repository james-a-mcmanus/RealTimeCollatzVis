#ifndef DATAUPDATER_
#define DATAUPDATER_

class DataUpdater : public SequenceHolder {
public:
	int sequence_len;
	int buffer_len;
	DataUpdater(int sequence_len, int buffer_len);
	void closeConnections();
};

#endif