// mConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "Server.h"
#include "Client.h"

void printFileLines(const std::string& fileName) {
    std::ifstream file(fileName); // Open the file

    if (!file.is_open()) { // Check if the file was successfully opened
        std::cerr << "Error: Could not open the file " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) { // Read each line from the file
        std::cout << line << std::endl; // Print the line to the console
    }

    file.close(); // Close the file
}

void load_ASCII_Art(int fileCode) {

    if (fileCode == 1) {
        std::string fileName = "theM_ASCII.txt";
        printFileLines(fileName);
    }

    if (fileCode == 2) {
        std::string fileName = "theM2_ASCII.txt";
        printFileLines(fileName);
    }

    if (fileCode == 3) {
        std::string fileName = "theX_ASCII.txt";
        printFileLines(fileName);
    }
}

int main()
{
    load_ASCII_Art(2);
    std::cout << "Welcome to the Madrets Console App!\n\n";

    std::thread myThread_1(Server);
    myThread_1.detach();

    Client();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
