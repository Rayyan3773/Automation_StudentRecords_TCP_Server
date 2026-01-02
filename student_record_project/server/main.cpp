#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    //wsa start
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    //create server socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Server socket creation failed.\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //bind
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Bind failed.\n";
        return 1;
    }

    //listen
    listen(serverSocket, 1);
    std::cout << "Server running. Waiting for connection...\n";

    //accept client
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Client accept failed.\n";
        return 1;
    }

    std::cout << "Client connected! Receiving data...\n";

    //open output file
    std::ofstream outFile("output.csv");
    if (!outFile.is_open()) {
        std::cout << "Could not open output.csv\n";
        return 1;
    }

    //revieve data
    char buffer[1024];
    int totalLines = 0;

    while (true) {
        int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0) {
            break; // no more data
        }

        buffer[bytes] = '\0'; // to terminate null

        std::string data(buffer);

        // write to file
        outFile << data;

        // line count
        for (char c : data) {
            if (c == '\n') totalLines++;
        }
    }

    std::cout << "Received " << totalLines << " records.\n";
    std::cout << "Saved to output.csv\n";

    //clean
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
