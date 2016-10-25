#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <string.h>
#include <vector>
#include <chrono>
#include "Socket.hpp"

using namespace std;

mutex mt;

//Manipula o vetor de string para cada player
void player_handler(Socket player, int player_id, vector<char*>* buffer){
	cout << "Thread Iniciada: Player " << player_id << endl;
	while(true){
		player.recv(1, buffer->at(player_id), 1024);

		if(string(buffer->at(player_id)) == "bye"){
			break;
		}
	}
}

void game_server(vector<Socket>* players){
	vector<char*>* buffer = new vector<char*>;
	vector<thread*> *threads = new vector<thread*>;
	string msg;
	bool bye;
	char* bye_msg = new char[1024];

	memset(bye_msg, '\0', 1024);
	msg = "bye";
	msg.copy(bye_msg, msg.size(), 0);

	cout << "Novo jogo inciado!" << endl;
	cout << "Esta partida será entre " << players->size() << " jogadores" << endl;

	//Cria um buffer pra cada player
	for(int i = 0; i < players->size(); i++){
		char* b = new char[1024];
		buffer->push_back(b);
	}

	//Cria uma thread pra cada player
	for(int i = 0; i < players->size(); i++){
		thread* new_player_handler = new thread(player_handler, players->at(i), i, buffer);
		threads->push_back(new_player_handler);
	}

	while(true){
		bye = false;
		for(int i = 0; i < buffer->size(); i++){
			mt.lock();
			msg = string(buffer->at(i));
			mt.unlock();
			if(msg == "bye"){
				bye = true;
			}
			cout << msg << endl;
		}

		if(bye){
			for(int i = 0; i < players->size(); i++){
				players->at(i).send(1, bye_msg, 1024);
			}

			//Encerra as threads player_handlers
			for(int i = 0; i < threads->size(); i++){
				threads->at(i)->join();
			}

			break;
		}else{
			for(int i = 0; i < players->size(); i++){
				for(int j = 0; j < players->size(); j++){
					if(i != j){
						players->at(i).send(1, buffer->at(j), 1024);
					}
				}
			}
		}

		this_thread::sleep_for(chrono::seconds(1));
	}

}

void players_receptionist(string ip, int port, int num_players){
	//Cria socket local
	Socket server_socket(ip, port);
	server_socket.bind();
	server_socket.listen(1);

	//Aguarda conexões enquanto o server permanecer aberto
	while(true){
		//Vetor contendo o número máximo de jogadores por partidas
		vector<Socket>* players = new vector<Socket>;
		cout << "Aguardando " << num_players << " jogadores..." << endl;
		for(int i = 0; i < num_players; i++){
			//mt.lock();
			server_socket.accept();
			cout << "Jogador " << i << " conectou!" << endl;
			players->push_back(server_socket);
			//mt.unlock();
		}

		cout << "Número de jogadores completos, inciando novo jogo..." << endl;
		thread* new_game_server = new thread(game_server, players);
		//threads.push_back(new_game_server);

		/*for(int i = 0; i < threads.size(); i++){
			if(threads.at(i)->joinable()){
				threads.at(i)->join();
				threads.erase(threads.begin() + i);
			}
		}*/
	}
}

int main(int argc, char **argv){

	string ip = string(argv[1]);
	int port = atoi(argv[2]);
	int num_players = atoi(argv[3]);

	cout << "Bem vindo!" << endl;
	cout << "IP: " << ip << endl;
	cout << "Porta: " << port << endl;
	cout << "Número de jogadores: " << num_players << endl;

	cout << "Inciando thread recepcionista..." << endl;
	thread new_receptionist(players_receptionist, ip, port, num_players);
	new_receptionist.join();

	return 0;
}
