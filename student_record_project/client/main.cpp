#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "student.h"
#include "utils.h"

int main() {

    // ---------------- Load Students ----------------
    std::string filename = "../students.txt";

    auto startLoad = std::chrono::high_resolution_clock::now();
    std::vector<Student> list = loadStudents(filename);
    auto endLoad = std::chrono::high_resolution_clock::now();

    auto loadTime = std::chrono::duration_cast<std::chrono::milliseconds>(endLoad - startLoad).count();
    std::cout << "Loaded " << list.size() << " students in " << loadTime << " ms\n";


    // ---------------- Sort Students ----------------
    auto startSort = std::chrono::high_resolution_clock::now();
    sortStudentsById(list);
    auto endSort = std::chrono::high_resolution_clock::now();

    auto sortTime = std::chrono::duration_cast<std::chrono::milliseconds>(endSort - startSort).count();
    std::cout << "Sorting took: " << sortTime << " ms\n";


    // ---------------- Setup TCP Connection ----------------
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Socket creation failed.\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9000); // port number
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "Connecting to server...\n";
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Connection failed. Start the server first.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected! Sending data...\n";

    // Measure sending time
    auto startSend = std::chrono::high_resolution_clock::now();

    // Send student records line by line
    for (const auto &s : list) {
        std::string line = 
            std::to_string(s.id) + "," + 
            s.name + "," + 
            std::to_string(s.age) + "," + 
            s.grade + "\n";

        send(clientSocket, line.c_str(), line.size(), 0);
    }

    auto endSend = std::chrono::high_resolution_clock::now();
    auto sendTime = std::chrono::duration_cast<std::chrono::milliseconds>(endSend - startSend).count();

    std::cout << "Sending completed in " << sendTime << " ms\n";

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}

//g++ main.cpp -o client_app -lws2_32
//g++ main.cpp -o server_app -lws2_32
