#pragma once

class ChatServer {
public:
    ChatServer(int port);
    void start();

private:
    int port; 
};