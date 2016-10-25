#include "Socket.hpp"

Socket::Socket(string ip, int port){
    addr = new sockaddr_in;
    my_socket = new int;
    new_socket = new int;

    addr->sin_family = AF_INET;
    inet_pton ( AF_INET, ip.c_str(), &(addr->sin_addr));
    addr->sin_port = htons(port);

    *my_socket = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::Socket(const Socket& socket){
	addr = new sockaddr_in;
    my_socket = new int;
    new_socket = new int;

	*(this->addr) = *(socket.addr);
	*(this->my_socket) = *(socket.my_socket);
	*(this->new_socket) = *(socket.new_socket);
}

Socket::~Socket(){
    delete addr;
    delete my_socket;
    delete new_socket;
}

//Main methods
void Socket::accept(){
    *new_socket = ::accept(*my_socket, (struct sockaddr *) NULL, NULL);
}

int Socket::bind(){
    return ::bind(*my_socket, (struct sockaddr *) addr, sizeof(*addr));
}

int Socket::connect(){
    return ::connect(*my_socket, (struct sockaddr *) addr, sizeof(*addr));
}

int Socket::close(int wich){
    if(wich == 0){
        return ::close(*my_socket);
    }else{
        return ::close(*new_socket);
    }
}

int Socket::listen(int limit){
    return ::listen(*my_socket, limit);
}

//Send and Receive
int Socket::send(int wich, char* buffer, int buffer_size){
    int sizesnd;
    if(wich == 0){
        sizesnd = ::send(*my_socket, buffer, buffer_size, MSG_WAITALL);
    }else{
        sizesnd = ::send(*new_socket, buffer, buffer_size, MSG_WAITALL);
    }

    return sizesnd;
}

int Socket::recv(int wich, char* buffer, int buffer_size){
    int sizercv;
    if(wich == 0){
        sizercv = ::recv(*my_socket, buffer, buffer_size, MSG_WAITALL);
    }else{
        sizercv = ::recv(*new_socket, buffer, buffer_size, MSG_WAITALL);
    }
    return sizercv;
}

int Socket::get_my_socket(){
	return *my_socket;
}

int Socket::get_new_socket(){
	return *new_socket;
}
