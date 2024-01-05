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

int main(){

    int socketDescriptor;
    int clientSocket;
    if (setupSocket(&clientSocket, &socketDescriptor) != 0){
        std::cerr << "Error Setting Up Socket" << std::endl;
        return -1;
    }
    int bytesAvailable = 128;
    int maxSequenceLen = 5000;

    DataUpdater dataHandler(socketDescriptor, clientSocket, maxSequenceLen, bytesAvailable);

    //SequenceHolder sequence(maxSequenceLen, clientSocket, bytesAvailable);
    // Read from the socket in 200ms intervals.
    do
    {
        dataHandler.receiveMessage();
        dataHandler.addFromMessage();
        std::cout << dataHandler.front() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } while(true); //
    
    // close client and server.
    dataHandler.closeConnections();

	return 0;
}