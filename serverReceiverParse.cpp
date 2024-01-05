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

int main(){

    int socketDescriptor;
    int clientSocket;
    if (setupSocket(&socketDescriptor, &clientSocket) != 0){
        std::cerr << "Error Setting Up Socket" << std::endl;
        return -1;
    }

    int bytesAvailable = 128;
    int maxSequenceLen = 5000;
    //std::vector<unsigned char> buffer(bytesAvailable);
    SequenceHolder sequence(maxSequenceLen, clientSocket, bytesAvailable);
    // Read from the socket in 200ms intervals.
    do
    {
        sequence.receiveMessage();
        sequence.addFromMessage();
        std::cout << sequence.front() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } while(true); //

    // Close the client socket
    std::cout <<"closing connection\n";
    close(clientSocket);

    // Close the server socket
    //close(socketDescriptor);

	return 0;
}