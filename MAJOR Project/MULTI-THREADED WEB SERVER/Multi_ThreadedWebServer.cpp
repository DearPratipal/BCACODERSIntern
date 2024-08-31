#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <mutex>

using namespace std;

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

mutex mtx; // Mutex for thread-safe printing

// Function to handle client connections
void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    // Read the client's request
    read(clientSocket, buffer, BUFFER_SIZE - 1);

    // Lock the mutex for thread-safe printing
    mtx.lock();
    cout << "Received request:\n" << buffer << endl;
    mtx.unlock();

    // Prepare a simple HTTP response
    string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    response += "<html><body><h1>Welcome to the Multi-Threaded Web Server!</h1></body></html>";

    // Send the response back to the client
    write(clientSocket, response.c_str(), response.length());

    // Close the client socket
    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Failed to create socket." << endl;
        return 1;
    }

    // Set up the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed." << endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) < 0) {
        cerr << "Listen failed." << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Server is running on port " << PORT << "..." << endl;

    vector<thread> threads; // Vector to store threads

    while (true) {
        // Accept a new client connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            cerr << "Failed to accept connection." << endl;
            continue;
        }

        // Lock the mutex for thread-safe printing
        mtx.lock();
        cout << "Accepted new connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;
        mtx.unlock();

        // Launch a new thread to handle the client
        threads.emplace_back(thread(handleClient, clientSocket));
    }

    // Cleanup: join threads (infinite loop prevents reaching this part, so it's for demonstration)
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
