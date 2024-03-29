#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "messageParser.h"
#include "SequenceHolder.h"
#include "DataUpdater.h"

// Class to hold the sequence data, possibly later implement more meta functions.
DataUpdater::DataUpdater(int sequence_len, int mssg_len, int num_mssg) : SequenceHolder(sequence_len, mssg_len, num_mssg){
	this->sequence_len = sequence_len;
}

// Close 
void DataUpdater::closeConnections(){
	std::cout <<"closing connection\n" << std::endl;
	close(this->clientSocket);
	close(this->socketDescriptor);
}
