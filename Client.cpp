#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <chrono>
#pragma comment(lib, "ws2_32.lib")

void Client() {
    std::cout << "mClient: This is the mClient!\n";
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << std::endl;


    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        //return 1;
        return;   
    }

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        // return 1;
        return;
    }

    // Configure the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    // serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr); // I added this because the above function (inet_addr) is deprecated


    // Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed.\n";
        closesocket(clientSocket);
        WSACleanup();
        // return 1;
        return;
    }

    std::cout << "mClient: Connected to server.\n";

    // Send a message
    const char* message = "Hello from client!";
    send(clientSocket, message, strlen(message), 0);

    // Receive and print response
    char buffer[512];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "mClient: Server responded with the following...\n";
        std::cout << "mClient: " << buffer << '\n';
    }

    // Close socket
    closesocket(clientSocket);
    WSACleanup();
    std::cout << "mClient: Exiting...\n";

    // return 0;
}




/*
Client Code
The client program:

1. Initializes Winsock:
    - Sets up the networking library (Winsock) to use TCP/IP protocols.

2. Creates a Socket:
    - The client creates a socket for connecting to the server.

3. Connects to the Server:
    - The client specifies the server's IP address (e.g., 127.0.0.1 for localhost) and port (54000) to establish a connection.

4. Sends Data:
    - The client sends a simple message ("Hello from client!") to the server.

5. Receives a Response:
    - The client waits for the server to respond with the same message (echoed back).

6. Closes the Socket:
    - After the communication, the client shuts down the connection.


Flow of Communication

1. Server starts and listens for connections.
2. Client connects to the server.
3. Client sends a message to the server.
4. Server receives the message and echoes it back.
5. Client receives the echoed message.


Use Case

This program is a basic example of TCP socket communication, often used in:

1. Learning network programming concepts.
2. Implementing small-scale client-server systems (e.g., chat applications, basic file transfer).
3. Prototyping before scaling to more complex systems (This is the plan).

*/

