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

DataUpdater::DataUpdater(int socketDescriptor, int clientSocket, int sequence_len, int buffer_len) : SequenceHolder(sequence_len, clientSocket, buffer_len) {
	this->socketDescriptor = socketDescriptor;
	this->clientSocket = clientSocket;
	this->sequence_len = sequence_len;
	this->buffer_len = buffer_len;
}