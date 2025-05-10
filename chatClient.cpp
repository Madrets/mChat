#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <atomic>
#include <string>
#include "chatClient.h"
#pragma comment(lib, "ws2_32.lib")

ChatClient::ChatClient(const std::string& ip, int port)
    : serverIp(ip), serverPort(port) {
}

void ChatClient::start() {
    std::cout << "ChatClient: Starting client...\n";

    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    std::atomic<bool> running(true);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "ChatClient: WSAStartup failed.\n";
        return;
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "ChatClient: Socket creation failed.\n";
        WSACleanup();
        return;
    }

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    //inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr.s_addr);
    if (serverIp == "localhost") {
        inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr);
    }
    else {
        inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr.s_addr);
    }

    // Connect to server
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "ChatClient: Connection failed.\n";
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    std::cout << "ChatClient: Connected to server.\n";

    // Thread for receiving messages
    std::thread receiveThread([&]() {
        char buffer[512];
        while (running) {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                std::cout << "\nChatClient: Server disconnected.\n";
                running = false;
                break;
            }
            buffer[bytesReceived] = '\0';
            std::cout << "\nServer: " << buffer << std::endl;  // print received message
            std::cout << "Client (You): " << std::flush; // Restore prompt cleanly
        }
     });

    // Main thread handles sending
    std::string input;
    while (running) {
        std::cout << "Client (You): ";
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
    WSACleanup();
    std::cout << "\nChatClient: Shutting down.";
}