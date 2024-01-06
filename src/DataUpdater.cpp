#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <iomanip>

#include <thread>
#include <chrono>

#include "messageParser.h"
#include "SequenceHolder.h"
#include "DataUpdater.h"

// Wrapper function to 
DataUpdater::DataUpdater(int sequence_len, int mssg_len, int num_mssg) : SequenceHolder(sequence_len, mssg_len, num_mssg){
	this->sequence_len = sequence_len;
}

// Close 
void DataUpdater::closeConnections(){
	std::cout <<"closing connection\n" << std::endl;
	close(this->clientSocket);
	close(this->socketDescriptor);
}