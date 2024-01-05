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

void DataUpdater::closeConnections(){
	std::cout <<"closing connection\n" << std::endl;
	close(this->clientSocket);
	close(this->socketDescriptor);
}

// helper function to setup the socket and connection.
int setupSocket(int* cs, int* sd){
    // Create a TCP socket
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketDescriptor == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Set up the server address and port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET; // addr family
    serverAddress.sin_port = htons(8080);  // Change this to your desired port
    serverAddress.sin_addr.s_addr = INADDR_ANY; // 

    // Bind the socket to the server address
    if (bind(socketDescriptor, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(socketDescriptor);
        return 1;
    }

    // Listen for incoming connections
    if (listen(socketDescriptor, SOMAXCONN) == -1) {
        std::cerr << "Failed to listen for connections" << std::endl;
        close(socketDescriptor);
        return 1;
    }

    std::cout << "Server listening on port 8080" << std::endl;

    // Accept an incoming connection
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(socketDescriptor, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength); // blocking
    if (clientSocket == -1) {
        std::cerr << "Failed to accept connection" << std::endl;
        close(socketDescriptor);
        return 1;
    }

    *cs = clientSocket;
    *sd = socketDescriptor;
    std::cout << "Client connected: " << inet_ntoa(clientAddress.sin_addr) << std::endl;
    return 0;
}