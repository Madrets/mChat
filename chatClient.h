#pragma once
#include <string>

class ChatClient {
public:
    ChatClient(const std::string& ip, int port);
    void start();

private:
    std::string serverIp;
    int serverPort;      
};