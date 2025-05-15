// mChat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <regex>
#include "chatServer.h"
#include "chatClient.h"

/*
// Function to print ASCII art from file
void printFileLines(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}
*/

// Wrapper to choose which ASCII file to print
void load_ASCII_Art(int fileCode) {
    if (fileCode == 1) {
        //printFileLines("theM_ASCII.txt");
    }
    else if (fileCode == 2) {
        //printFileLines("theM2_ASCII.txt");

        //This uses raw string literals(R"(...)") to preserve the ASCII layout
        std::cout << R"(

                                   .....:=*%@@@@@@@@@@@@%*=:.....                                   
                             ....:*%@@@@@@@@@@@@@@@@@@@@@@@@@@@@%*:....                             
                         ....=@@@@@@@@@@@@@@@@@%%##%%@@@@@@@@@@@@@@@@@-.....                        
                     ....-#@@@@@@@@@%+-......................-+%@@@@@@@@@#:...                      
                   ...:@@@@@@@@@+.....                       ......+@@@@@@@@%:....                  
                   .*@@@@@@@+.....                                 ...:*@@@@@@@*..                  
                 .@@@@@@@+....                                         ...*@@@@@@@..                
              .:@@@@@@#:.                                                  .:%@@@@@@..              
            ..@@@@@@+..                                                      ..*@@@@@%..            
          ..+@@@@@+..                                                          ..*@@@@@+..          
        ...@@@@@%....                                                          ....@@@@@@...        
        ..#@@@@:...                                                              ...-@@@@@=.        
        .=@@@@-..                                                                   ..%@@@@#        
        .%@@@%.                                                                       .+@@@@%..     
        .@@@@=.                                                                         -@@@@@...   
        .@@@@-.                                                                         .-@@@@@..   
        .%@@@@...                  ...........            .....  ......                   -@@@@*.   
        .:@@@@@@@#****#####%%+.. ...+@@@@@@@@@+....   ...-#@@@@@@@@@@@#:..                .=@@@@-.. 
        ...#@@@@@@@@@@@@@@@@@@#..=@@@@@@@@@@@@@@@*....-@@@@@@@@@@@@@@@@@@=..              ..#@@@@:. 
  ...     ....*%@@@@@@@@@@@@@@%-@@@@@@@%%%@@@@@@@@@+-@@@@@@@%#++*%@@@@@@@@%...              .@@@@*. 
  .-...       ..........=@@@@@@@@@@=.........=@@@@@@@@@@@%.....  ...-@@@@@@#..              .-@@@@: 
.#@@@+.                ..%@@@@@@@*..          .%@@@@@@@@+..          .@@@@@@=.              ..@@@@*.
:@@@@-.                  *@@@@@@+.            .:@@@@@@@+.            .-@@@@@%.                +@@@@.
=@@@@..                  *@@@@@@..            ..@@@@@@@..            ..@@@@@@:                .@@@@-
*@@@@..                  *@@@@@=..            ..@@@@@@*..              %@@@@@-                .@@@@+
%@@@#..                  *@@@@@:                %@@@@@=                *@@@@@=                .%@@@#
@@@@*..                  *@@@@@.                *@@@@@-                +@@@@@=                .#@@@%
@@@@+ .                  *@@@@@.                *@@@@@:                *@@@@@=                .*@@@%
@@@@+..                  *@@@@@.                *@@@@@:                *@@@@@=                .#@@@%
%@@@#..                  *@@@@@.                *@@@@@:                *@@@@@=                .%@@@#
*@@@@..                  *@@@@@.                *@@@@@:                *@@@@@=                .@@@@*
=@@@@..                  *@@@@@.                *@@@@@:                *@@@@@=                .@@@@=
:@@@@:.                  *@@@@@.                *@@@@@:                *@@@@@=              ..=@@@@.
.%@@@@.                ..*@@@@@.              ..%@@@@@:              ..#@@@@@+..            ..@@@@#.
.-@@@@:..        ........@@@@@@=......  ........@@@@@@=.. ....   ......@@@@@@%........      .:@@@@-.
..@@@@@..        +%@@@@@@@@@@@@@@@@@%.  .-%@@@@@@@@@@@@@@@@%+..  +@@@@@@@@@@@@@%%%@@%:      .@@@@%. 
  :@@@@=.     ..*@@@@@@@@@@@@@@@@@@@@%  .%@@@@@@@@@@@@@@@@@@@-..:@@@@@@@@@@@@@@@@@@@@@:.    +@@@@:. 
  .*@@@@:..   ...@@@@@@@@%###%%@@@@@@:  .-@@@@@@%#**#%%@@@@@@....#@@@@@@%###%@@@@@@@@*..  .-@@@@=.. 
  ..@@@@@..                                                                               :@@@@%.   
    .@@@@@...                                                                           .:@@@@@..   
    ..@@@@@..                                                                         ..:@@@@@.     
    ...@@@@@:..                                                                       .-@@@@@..     
      ..@@@@@+...                                                                   ..*@@@@%...     
      ...#@@@@%..                                                                   .@@@@@*.        
        ..=@@@@@=..                                                              ..*@@@@@-..        
          ..%@@@@@-..                                                          ..=@@@@@#..          
            .:@@@@@@-..                                                      ..-@@@@@@:.            
              .=@@@@@@+..                                                ....+@@@@@@-.              
               ..-@@@@@@%:....                                         ...:@@@@@@@-...              
                 ..:%@@@@@@%-.....                                 ....-%@@@@@@%:...                
                   ...+@@@@@@@@*..                                 :#@@@@@@@@=....                  
                       ..*@@@@@@@@@@+-..                     .-+@@@@@@@@@@+...                      
                         ...:#@@@@@@@@@@@@@%%*+==--==+#%%@@@@@@@@@@@@@#:..                          
                             ....*%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%+..                               
                                   ...:-+#@@@@@@@@@@@@@@@@#+-:.                                     

        )" << std::endl;
    }
    else if (fileCode == 3) {
        //printFileLines("theX_ASCII.txt");
    }
}

// Check if Ip argument is valid
bool isValidIp(const std::string& ip) {
    if (ip == "localhost") return true;

    std::regex ipRegex(R"(^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$)");
    std::smatch match;

    if (std::regex_match(ip, match, ipRegex)) {
        for (int i = 1; i <= 4; ++i) {
            int octet = std::stoi(match[i]);
            if (octet < 0 || octet > 255) return false;
        }
        return true;
    }

    return false;
}

// Check if Port argument is valid
bool isValidPort(const std::string& portStr, int& port) {
    try {
        port = std::stoi(portStr);
        return port > 0 && port <= 65535;
    }
    catch (...) {
        return false;
    }
}

int main(int argc, char* argv[]) {
    std::cout << std::endl;
    load_ASCII_Art(2);
    std::cout << "Welcome to the mChat App!\n\n";

    if (argc < 3) {
        std::cerr << "Usage for server: " << argv[0] << " server <port>\n";
        std::cerr << "Usage for client: " << argv[0] << " client <server_ip> <port>\n";
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "server") {
        int port;
        if (!isValidPort(argv[2], port)) {
            std::cerr << "Error: Invalid port number.\n";
            std::cerr << "Usage for server: " << argv[0] << " server <port>\n";
            return 1;
        }
        ChatServer server(port);
        server.start();
    }
    else if (mode == "client") {
        if (argc < 4) {
            std::cerr << "Error: Missing arguments. Usage: client <server_ip> <port>\n";
            return 1;
        }

        std::string ip = argv[2];
        int port;

        if (!isValidIp(ip)) {
            std::cerr << "Error: Invalid IP address.\n";
            std::cerr << "Usage for server: " << argv[0] << " server <port>\n";
            std::cerr << "Usage for client: " << argv[0] << " client <server_ip> <port>\n";
            return 1;
        }
        if (!isValidPort(argv[3], port)) {
            std::cerr << "Error: Invalid port number.\n";
            std::cerr << "Usage for server: " << argv[0] << " server <port>\n";
            std::cerr << "Usage for client: " << argv[0] << " client <server_ip> <port>\n";
            return 1;
        }

        ChatClient client(ip, port);
        client.start();
    }
    else {
        std::cerr << "Error: Unknown mode '" << mode << "'. Use 'server' or 'client'.\n";
        std::cerr << "Usage for server: " << argv[0] << " server <port>\n";
        std::cerr << "Usage for client: " << argv[0] << " client <server_ip> <port>\n";
        return 1;
    }

    return 0;
}


/* 
int main()
{
    load_ASCII_Art(2);
    std::cout << "Welcome to the mChat App!\n\n";

    std::thread myThread_1(Server);
    myThread_1.detach();

    Client();
}

*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
