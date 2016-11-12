#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <string.h>
#include <vector>
#include <chrono>
#include "Map.hpp"
#include "Socket.hpp"
#include "Player.hpp"
#include "Ghost.hpp"

using namespace std;

mutex mt;

//Verifica colisão do pac-man
bool collide(Player* player, Map* g_map, int direction, bool last_try){

	bool p_w = false;
	char v;

	switch(direction){
		case 0:
			for(int j = 0; j < 16; j++){
				v = g_map->get_map_at(player->get_i() + 16, player->get_j() + j);

				if(v == '1'){
					p_w = true;
				}
			}

			if(!p_w){
				//Poso mover o pac
				g_map->set_map_at(player->get_i(), player->get_j(), '0');
				player->set_i(player->get_i() + 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '5'){
					//Remove o biscuit da lista de biscuits
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '6'){
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_s_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_s_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->fill_super_force();

					//muda direção
					player->set_direction(player->get_desired_direction());

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '7'){
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//Pega o item
					player->set_item(7);

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '4'){
					//KILL PAC-MAN
					//verifica se esta super
					//Define sprite
					//seta número de lifes
				}else{
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}

				//Define sprite
				if(player->get_sprites_num() == 0){
					player->set_sprites_num(1);
				}else
				if(player->get_sprites_num() == 1){
					player->set_sprites_num(2);
				}else
				if(player->get_sprites_num() == 2){
					player->set_sprites_num(0);
				}else{
					player->set_sprites_num(0);
				}

				return true;

			}else{
				if(last_try){
					//Define sprite
					player->set_sprites_num(2);
					//Verifica super
					player->decrease_super_force();
				}
				return false;
			}
		break;

		case 1:
			for(int j = 0; j < 16; j++){
				v = g_map->get_map_at(player->get_i() - 1, player->get_j() + j);

				if(v == '1'){
					p_w = true;
				}
			}

			if(!p_w){
				//Poso mover o pac
				g_map->set_map_at(player->get_i(), player->get_j(), '0');
				player->set_i(player->get_i() - 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '5'){
					//Remove o biscuit da lista de biscuits
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '6'){
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_s_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_s_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->fill_super_force();

					//muda direção
					player->set_direction(player->get_desired_direction());

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '7'){
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//Pega o item
					player->set_item(7);

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '4'){
					//KILL PAC-MAN
					//verifica se esta super
					//Define sprite
					//seta número de lifes
				}else{
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}

				//Define sprite
				if(player->get_sprites_num() == 0){
					player->set_sprites_num(3);
				}else
				if(player->get_sprites_num() == 3){
					player->set_sprites_num(4);
				}else
				if(player->get_sprites_num() == 4){
					player->set_sprites_num(0);
				}else{
					player->set_sprites_num(0);
				}

				return true;

			}else{
				if(last_try){
					//Define sprite
					player->set_sprites_num(4);
					//Verifica super
					player->decrease_super_force();
				}
				return false;
			}
		break;

		case 2:
			for(int j = 0; j < 16; j++){
				v = g_map->get_map_at(player->get_i() + j, player->get_j() + 16);

				if(v == '1'){
					p_w = true;
				}
			}

			if(!p_w){
				//Poso mover o pac
				g_map->set_map_at(player->get_i(), player->get_j(), '0');
				player->set_j(player->get_j() + 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '5'){
					//Remove o biscuit da lista de biscuits
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '6'){
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_s_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_s_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->fill_super_force();

					//muda direção
					player->set_direction(player->get_desired_direction());

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '7'){
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//Pega o item
					player->set_item(7);

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '4'){
					//KILL PAC-MAN
					//verifica se esta super
					//Define sprite
					//seta número de lifes
				}else{
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}

				//Define sprite
				if(player->get_sprites_num() == 0){
					player->set_sprites_num(5);
				}else
				if(player->get_sprites_num() == 5){
					player->set_sprites_num(6);
				}else
				if(player->get_sprites_num() == 6){
					player->set_sprites_num(0);
				}else{
					player->set_sprites_num(0);
				}

				return true;

			}else{
				if(last_try){
					//Define sprite
					player->set_sprites_num(6);
					//Verifica super
					player->decrease_super_force();
				}
				return false;
			}
		break;

		case 3:
			for(int j = 0; j < 16; j++){
				v = g_map->get_map_at(player->get_i() + j, player->get_j() - 1);

				if(v == '1'){
					p_w = true;
				}
			}

			if(!p_w){
				//Poso mover o pac
				g_map->set_map_at(player->get_i(), player->get_j(), '0');
				player->set_j(player->get_j() - 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '5'){
					//Remove o biscuit da lista de biscuits
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '6'){
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map->get_s_biscuits()->find(make_pair(player->get_i(), player->get_j()));
					g_map->get_s_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player->set_eaten_biscuits(player->get_eaten_biscuits() + 1);

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->fill_super_force();

					//muda direção
					player->set_direction(player->get_desired_direction());

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '7'){
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//Pega o item
					player->set_item(7);

					//muda direção
					player->set_direction(direction);

				}else
				if(g_map->get_map_at(player->get_i(), player->get_j()) == '4'){
					//KILL PAC-MAN
					//verifica se esta super
					//Define sprite
					//seta número de lifes
				}else{
					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

					//verifica super
					player->decrease_super_force();

					//muda direção
					player->set_direction(direction);

				}

				//Define sprite
				if(player->get_sprites_num() == 0){
					player->set_sprites_num(7);
				}else
				if(player->get_sprites_num() == 7){
					player->set_sprites_num(8);
				}else
				if(player->get_sprites_num() == 8){
					player->set_sprites_num(0);
				}else{
					player->set_sprites_num(0);
				}

				return true;

			}else{
				if(last_try){
					//Define sprite
					player->set_sprites_num(8);
					//Verifica super
					player->decrease_super_force();
				}
				return false;
			}
		break;
	}
}


void move_ghost(Map* g_map, Ghost* g){
	int u, r, d, l;
	u = (g->get_i() - 48) > 0 ? (g->get_i() - 48) : 0;
	d = (g->get_i() + 48) < 248 ? (g->get_i() - 48) : 248;

	l = (g->get_j() - 48) > 0 ? (g->get_j() - 48) : 0;
	r = (g->get_i() + 48) < 248 ? (g->get_i() - 48) : 248;
}

//Manipula o vetor de string para cada player
void player_handler(Socket player_scoket, int player_id, vector<char*>* buffer){
	cout << "Thread Iniciada: Player " << player_id << endl;
	while(true){
		player_scoket.recv(1, buffer->at(player_id), 10);
		if(string(buffer->at(player_id)) == "36"){
			break;
		}
	}
}

void game_server(vector<Socket>* player_scoket){
	//Vetor de buffers
	vector<char*>* buffers = new vector<char*>;
	//Vetor de threads
	vector<thread*> *threads = new vector<thread*>;

	//Mapa
	Map* g_map = new Map(224, 248, "map1_1.txt");

	//Jogadores
	vector<Player*> players;

	//Fantasmas
	vector<Ghost*> ghosts;

	//Mensagens
	string msg;
	char* buffer_dots = new char[2048];
	char* buffer_info = new char[2048];

	//Guarda características de jogadores
	for(int i = 0; i < player_scoket->size(); i++){
		pair<int, int> pos = g_map->get_initial_player_pos()->at(i);
		Player* player = new Player(pos.first, pos.second);
		players.push_back(player);
	}

	//Guarda características dos fantas
	for(int i = 0; i < g_map->get_initial_ghost_pos()->size(); i++){
		pair<int, int> pos = g_map->get_initial_ghost_pos()->at(i);
		Ghost* ghost = new Ghost(pos.first, pos.second);
		ghosts.push_back(ghost);
	}

	ghosts.at(0)->reset_wait_time();

	//Cria um buffer pra cada player
	for(int i = 0; i < player_scoket->size(); i++){
		char* b = new char[10];
		buffers->push_back(b);
	}

	//Cria uma thread pra cada player
	for(int i = 0; i < player_scoket->size(); i++){
		thread* new_player_handler = new thread(player_handler, player_scoket->at(i), i, buffers);
		threads->push_back(new_player_handler);
	}

	map<pair<int,int>,char>::iterator it;
	while(/*g_map->get_biscuits()->size() != 0*/true){
		//Para cada jogador, realiza o processamento
		for(int i = 0; i < players.size(); i++){
			mt.lock();
			if(string(buffers->at(i)) == "71"){
				players.at(i)->set_desired_direction(3);
			}else
			if(string(buffers->at(i)) == "72"){
				players.at(i)->set_desired_direction(2);
			}else
			if(string(buffers->at(i)) == "73"){
				players.at(i)->set_desired_direction(1);
			}else
			if(string(buffers->at(i)) == "74"){
				players.at(i)->set_desired_direction(0);
			}
			mt.unlock();

			if(players.at(i)->get_lifes() != 0){
				switch(players.at(i)->get_direction()){
					case 0:
						switch(players.at(i)->get_desired_direction()){
							case 0:
								collide(players.at(i), g_map, 0, true);
							break;

							case 1:
								if(!collide(players.at(i), g_map, 1, false)){
									collide(players.at(i), g_map, 0, true);
								}
							break;

							case 2:
								if(!collide(players.at(i), g_map, 2, false)){
									collide(players.at(i), g_map, 0, true);
								}
							break;

							case 3:
								if(!collide(players.at(i), g_map, 3, false)){
									collide(players.at(i), g_map, 0, true);
								}
							break;
						}
					break;

					//############################## 1 #################################
					case 1:
						switch(players.at(i)->get_desired_direction()){
							case 0:
								if(!collide(players.at(i), g_map, 0, false)){
									collide(players.at(i), g_map, 1, true);
								}
							break;

							case 1:
								collide(players.at(i), g_map, 1, true);
							break;

							case 2:
								if(!collide(players.at(i), g_map, 2, false)){
									collide(players.at(i), g_map, 1, true);
								}
							break;

							case 3:
								if(!collide(players.at(i), g_map, 3, false)){
									collide(players.at(i), g_map, 1, true);
								}
							break;
						}
					break;

					case 2:
						switch(players.at(i)->get_desired_direction()){
							case 0:
								if(!collide(players.at(i), g_map, 0, false)){
									collide(players.at(i), g_map, 2, true);
								}
							break;

							case 1:
								if(!collide(players.at(i), g_map, 1, false)){
									collide(players.at(i), g_map, 2, true);
								}
							break;

							case 2:
								collide(players.at(i), g_map, 2, true);
							break;

							case 3:
								if(!collide(players.at(i), g_map, 3, false)){
									collide(players.at(i), g_map, 2, true);
								}
							break;
						}
					break;

					case 3:
						switch(players.at(i)->get_desired_direction()){
							case 0:
								if(!collide(players.at(i), g_map, 0, false)){
									collide(players.at(i), g_map, 3, true);
								}
							break;

							case 1:
								if(!collide(players.at(i), g_map, 1, false)){
									collide(players.at(i), g_map, 3, true);
								}
							break;

							case 2:
								if(!collide(players.at(i), g_map, 2, false)){
									collide(players.at(i), g_map, 3, true);
								}
							break;

							case 3:
								collide(players.at(i), g_map, 3, true);
							break;
						}
					break;
				}
			}
		}

		//Mensagem já pode ser gerada
		//Envia os biscuits e super biscuits
		msg = "";
		for(it = g_map->get_biscuits()->begin(); it != g_map->get_biscuits()->end(); it++){
			msg += string(to_string(it->first.first) + "x" + to_string(it->first.second) + ";");
		}

		for(it = g_map->get_s_biscuits()->begin(); it != g_map->get_s_biscuits()->end(); it++){
			msg += string("S" + to_string(it->first.first) + "x" + to_string(it->first.second) + ";");
		}

		memset(buffer_dots, '\0', 2048);
		msg.copy(buffer_dots, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_dots, 2048);
		}

		//Envia atributos de clientes
		msg = "";
		for(int i = 0; i < players.size(); i++){
			msg += string(to_string(players.at(i)->get_i()) + "|" + to_string(players.at(i)->get_j()) + "|" +
			to_string(players.at(i)->get_sprites_num()) + "|" + to_string(players.at(i)->get_lifes()) + "|" +
			to_string(/*players.at(i)->get_sound_num()*/0) + "|" +
			to_string(players.at(i)->get_eaten_biscuits()) + "|" +
			to_string(players.at(i)->get_item()) + "|;");
		}

		memset(buffer_info, '\0', 2048);
		msg.copy(buffer_info, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_info, 2048);
		}

		//Enviar atributos dos fantasmas
		msg = "";
		for(int i = 0; i < ghosts.size(); i++){
			msg += string(to_string(ghosts.at(i)->get_i()) + "|" +
			to_string(ghosts.at(i)->get_j()) + "|" +
			to_string(ghosts.at(i)->get_sprites_num()) + "|;");
		}

		memset(buffer_info, '\0', 2048);
		msg.copy(buffer_info, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_info, 2048);
		}

		this_thread::sleep_for(chrono::milliseconds(20));
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
