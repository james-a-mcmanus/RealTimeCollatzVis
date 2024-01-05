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

DataUpdater::DataUpdater(int sequence_len, int buffer_len) : SequenceHolder(sequence_len, buffer_len) {
	//this->socketDescriptor = -1;
	//this->clientSocket = -1;
	this->sequence_len = sequence_len;
	this->buffer_len = buffer_len;
}

void DataUpdater::closeConnections(){
	std::cout <<"closing connection\n" << std::endl;
	close(this->clientSocket);
	close(this->socketDescriptor);
}