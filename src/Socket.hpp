#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

class Socket{
private:
    sockaddr_in* addr;
    int* my_socket;
    int* new_socket;

public:
    //Constructor and Destructor
    Socket();
    Socket(string ip, int port);
	Socket(const Socket& socket);
    ~Socket();

    //Main methods
    void accept();
    int bind();
    int connect();
    int close(int wich);
    int listen(int limit);

    //Send and Receive
    int send(int wich, char* buffer, int buffer_size);
    int recv(int wich, char* buffer, int buffer_size);

	int get_my_socket();
	int get_new_socket();
};
