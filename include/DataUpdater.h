#ifndef DATAUPDATER_
#define DATAUPDATER_

class DataUpdater : public SequenceHolder {
public:
	int sequence_len;
	DataUpdater(int sequence_len, int mssg_len, int num_mssg);
	void closeConnections();
};

#endif