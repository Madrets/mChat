# mChat

mChat is a lightweight, multithreaded client-server chat application written in C++ using Winsock, designed for real-time two-way communication over a network.

## Features

- Real-time text-based communication between client and server
- Multithreaded design to allow simultaneous message sending and receiving
- Console-based UI for ease of use
- Modular code structure for maintainability and future expansion

## Future Enhancements

- WAN support
- Message logging
- GUI front end

## Requirements

- Windows OS
- C++ compiler (Visual Studio recommended)
- Winsock2

## Getting Started

1. Clone this repository.
2. Open the project in Visual Studio.
3. Build the solution and run the executable. 
4. In one terminal, run the server:  
            `mChat.exe server <port>`
5. In the another terminal (or on a different computer), run the client:  
            `mChat.exe client <server_ip> <port>`

## Disclaimer

This project is for educational and personal use only. Redistribution or reuse of the code without permission is prohibited.

## License

See [LICENSE](LICENSE) for details.