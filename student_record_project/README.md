# Student Record Management System (C++)
This is a small project I made for the Sarla Aviation Software Intern assignment.  
The idea was to read student data from a file, do basic operations on it,  
and then send it from a client program to a server program.


# What the project does
1) Loads student records from `students.txt`  
2) Stores them in a struct + vector  
3) Supports listing, searching by ID, and sorting  
4) Measures basic performance (file load, sorting, sending time)  
5) Sends all the sorted records from the client to the server using a simple TCP socket  
6) The server saves the received data into `output.csv`

# Input File Format
The students.txt file contains records in the format:
id,name,age,grade

Example:
17,Isha,20,A

# Language and Libraries Used
- C++  
- Standard Library (vector, string, chrono, fstream, algorithm)  
- Winsock2 (for simple TCP networking on Windows)  


## Steps to Run

# Server:
In terminal 1:
cd server
g++ main.cpp -o server_app -lws2_32
.\server_app

# Client:
In terminal 2:
cd client
g++ main.cpp -o client_app -lws2_32
.\client_app


# Performance
- Students loaded: 30 
- File loading time: 0–1 ms  
- Sorting time: 0 ms  
- Sending time: 0–1 ms  

# Known Issues or Limitations
- Networking uses a basic TCP socket instead of full WebSocket protocol  
- No validation for incorrect or malformed student records  
- Server handles only one client connection at a time  
- Search is linear and can be optimized if needed  

# Bonus Features Implemented
- Basic modularity (separate header files for struct and utility functions)  
- Reusable functions for loading, searching, listing, and sorting  
- Simple error handling for file opening and socket failures  
- Performance measurement using std::chrono  

This project helped me revise file handling, basic data structures,  
simple networking, and working with multiple C++ files.