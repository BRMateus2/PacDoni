#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <string.h>
#include "Socket.hpp"

using namespace std;

mutex mt;

void thread_rcv(Socket client_game, bool* has_finish){
	cout << "Thread de recebimento inciada com sucesso!" << endl;

	char* buffer = new char[1024];
	string msg;

	while(true){
		memset(buffer, '\0', 1024);
		//mt.lock();
		client_game.recv(0, buffer, 1024);
		//mt.unlock();
		msg = string(buffer);

		if(msg == "bye"){
			*has_finish = true;
			break;
		}else{
			if(msg != ""){
				cout << "Mensagem recebida:" << endl;
				cout << msg << "\n\n";
			}
		}
	}
}

void thread_snd(Socket client_game, bool* has_finish){
	cout << "Thread de envio iniciado com sucesso!" << endl;

	char* buffer = new char[1024];
	string msg;

	cout << "Bem vindo, digite sua mensagem e pressione enter para enviar" << endl;
	while(true){
		if(*has_finish){
			break;
		}
		
		cout << "> ";
		memset(buffer, '\0', 1024);
		getline(cin,msg);

		if(msg == "bye"){
			msg.copy(buffer, msg.size(), 0);
			//mt.lock();
			client_game.send(0, buffer, 1024);
			//mt.unlock();
			break;
		}else{
			msg.copy(buffer, msg.size(), 0);
			//mt.lock();
			client_game.send(0, buffer, 1024);
			//mt.unlock();
		}
	}

}

int main(int argc, char **argv){

	string ip = string(argv[1]);
	int port = atoi(argv[2]);
	bool* has_finish = new bool(false);

	//Cria um atributo
	Socket client_game(ip, port);

	//Conecta ao servidor
	cout << "Iniciando conexão..." << endl;
	if(client_game.connect() == 0){

		cout << "Iniciando thread de envio..." << endl;
		thread* send = new thread(thread_snd, client_game, has_finish);
		cout << "Iniciando thread de recebimento..." << endl;
		thread* recv = new thread(thread_rcv, client_game, has_finish);

		recv->join();
		send->join();

		client_game.close(0);
	}else{
		cout << "Erro ao estabelecer conexão!" << endl;
	}



	return 0;
}
