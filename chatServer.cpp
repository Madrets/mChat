#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <atomic>
#include <string>
#include "chatServer.h"
#pragma comment(lib, "ws2_32.lib")

ChatServer::ChatServer(int port) : port(port) {}

void ChatServer::start() {
    std::cout << "ChatServer: Starting server...\n";

    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    std::atomic<bool> running(true);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "ChatServer: WSAStartup failed.\n";
        return;
    }

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "ChatServer: Socket creation failed.\n";
        WSACleanup();
        return;
    }

    // Bind to port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "ChatServer: Bind failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    // Listen for connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "ChatServer: Listen failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    std::cout << "ChatServer: Waiting for client...\n";

    // Accept client
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "ChatServer: Accept failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    std::cout << "ChatServer: Client connected.\n";

    // Thread for receiving messages
    std::thread receiveThread([&]() {
        char buffer[512];
        while (running) {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                std::cout << "\nChatServer: Client disconnected.\n";
                running = false;
                break;
            }
            buffer[bytesReceived] = '\0';
            std::cout << "\nClient: " << buffer << std::endl; // print received message
            std::cout << "Server (You): " << std::flush; // Restore prompt cleanly
        }
     });

    // Main thread handles sending
    std::string input;
    while (running) {
        std::cout << "Server (You): ";
        std::getline(std::cin, input);
        if (input == "/exit") {
            running = false;
            break;
        }
        send(clientSocket, input.c_str(), input.size(), 0);
    }

    // Cleanup
    receiveThread.join();
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    std::cout << "\nChatServer: Shutting down.";
}