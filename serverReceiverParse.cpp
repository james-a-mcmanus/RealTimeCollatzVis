#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include <thread>
#include <chrono>

//set functions to receive the series of incoming bytes
ssize_t fifo_receive(unsigned char *data, int len, int socketDescriptor)
{
    ssize_t bytesRead = recv(socketDescriptor, data, len, 0);
    return bytesRead;
};

//Checks how many bytes available to read from socket: probably opens us up to race condition...
int fifo_available(int socketDescriptor)
{
    int bytesAvailable;
    const int error = ioctl(socketDescriptor, FIONREAD, &bytesAvailable);
    return bytesAvailable;
};


int main(){

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

    std::cout << "Client connected: " << inet_ntoa(clientAddress.sin_addr) << std::endl;    

    do
    {
        int bytesAvailable = fifo_available(socketDescriptor);
        unsigned char* buffer = new unsigned char[bytesAvailable];
        ssize_t bytesRead = fifo_receive(buffer, bytesAvailable, socketDescriptor);
        printf("%.*s",bytesRead,buffer);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } while(true);


    // Close the client socket
    std::cout <<"closing connection\n";
    close(clientSocket);

    // Close the server socket
    close(socketDescriptor);

	return 0;
}