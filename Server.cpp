#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void Server() {
    std::cout << "mServer: This is the mServer!\n";

    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);

    // Initialize Winsock
    /*
        The WSADATA structure contains information about the Windows Sockets implementation.

        The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system, 
        and sets the passed version as the highest version of Windows Sockets support that the caller can use.
    */
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        // printf("WSAStartup failed: %d\n", iResult);
        // return 1;
        return;
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        // return 1;
        return;
    }

    // Configure the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(54000);

    // Bind the socket
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        //return 1;
        return;
    }

    // Listen for connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        // return 1;
        return;
    }

    std::cout << "mServer: Waiting for client connection...\n";

    // Accept a client connection
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        //return 1;
        return;
    }

    std::cout << "mServer: Client connected.\n";

    // Receive and echo message
    char buffer[512];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "mServer: I received the following message...\n";
        std::cout << "mServer: " << buffer << '\n';
        send(clientSocket, buffer, bytesReceived, 0);
    }

    // Close sockets
    std::cout << "mServer: Exiting...\n";
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    //return 0;
}


/*
https://learn.microsoft.com/en-us/windows/win32/winsock/using-winsock

Steps to Compile and Run
    1. Save the server and client code into separate files (e.g., server.cpp and client.cpp).
    2. Compile using a C++ compiler with Winsock support (e.g., MSVC):
            cl /EHsc server.cpp ws2_32.lib
            cl /EHsc client.cpp ws2_32.lib
    3. Run the server executable first, then run the client executable.

Key Points
    - Use the same port number (e.g., 54000) in both server and client code.
    - Use 127.0.0.1 as the server address for local communication.
    - Ensure the Winsock library is properly linked during compilation (ws2_32.lib).

*/

/*
Server Code
The server program:

1. Initializes Winsock:
    - Sets up the networking library (Winsock) to use TCP/IP protocols.

2. Creates a Listening Socket:
    - The socket is created to listen for incoming client connections.

3. Configures and Binds the Socket:
    - Binds the socket to a specific IP address (INADDR_ANY, which means "any available address") and a port (54000).

4. Listens for Connections:
    - The listen function puts the server socket into a state where it waits for incoming connection requests.

5. Accepts a Client Connection:
    - When a client connects, the server accepts it and creates a new socket (clientSocket) for communicating with that specific client.

6. Receives and Responds to Data:
    - The server waits for the client to send data, echoes it back to the client, and then closes the connection.


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