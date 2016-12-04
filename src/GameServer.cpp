#include <iostream>
#include <algorithm>
#include <mutex>
#include <thread>
#include <string>
#include <string.h>
#include <vector>
#include <chrono>
#include "Map.hpp"
#include "Socket.hpp"
#include "Player.hpp"

using namespace std;

mutex mt;

bool player_sort(Player* i, Player* j){
	if(i->get_eaten_biscuits() > j->get_eaten_biscuits()){
		return true;
	}else
	if(i->get_eaten_biscuits() == j->get_eaten_biscuits() && i->get_lifes() > j->get_lifes()){
		return true;
	}else{
		return false;
	}
}

bool wins_sort(pair<int, int> i, pair<int, int> j){
	return i.second > j.second;
}

//Verifica colisão do pac-man
bool collide(Player* player, Map* g_map, int direction, bool last_try, vector<Player*> ps){

	bool p_w = false;
	char v;
	int p_pos = -1;

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
				for(int i = 0; i < ps.size(); i++){
					if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j() &&
						ps.at(i)->get_id() != player->get_id()){
						p_pos = i;
					}
				}

				if(p_pos == -1){
					g_map->set_map_at(player->get_i(), player->get_j(), '0');
				}

				//Move o pac-man
				player->set_i(player->get_i() + 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '3'){
					//Procura por jogador
					for(int i = 0; i < ps.size(); i++){
						if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j()
						&& ps.at(i)->get_id() != player->get_id()){
							p_pos = i;
						}
					}

					//Colisão com outro jogador
					if(player->get_super_force() > 0 && ps.at(p_pos)->get_super_force() == 0 &&
						ps.at(p_pos)->get_time_wait() == 0){
						ps.at(p_pos)->fill_wait_time();
						ps.at(p_pos)->set_sprites_num(9);
						ps.at(p_pos)->set_lifes(ps.at(p_pos)->get_lifes() - 1);
						ps.at(p_pos)->set_sound_num(2);
					}

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');


				}else
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

					//muda o som
					player->set_sound_num(0);

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

					//muda o som
					player->set_sound_num(1);

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
				for(int i = 0; i < ps.size(); i++){
					if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j() &&
						ps.at(i)->get_id() != player->get_id()){
						p_pos = i;
					}
				}

				if(p_pos == -1){
					g_map->set_map_at(player->get_i(), player->get_j(), '0');
				}

				player->set_i(player->get_i() - 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '3'){
					//Procura por jogador
					for(int i = 0; i < ps.size(); i++){
						if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j()
						&& ps.at(i)->get_id() != player->get_id()){
							p_pos = i;
						}
					}

					//Colisão com outro jogador
					if(player->get_super_force() > 0 && ps.at(p_pos)->get_super_force() == 0 &&
						ps.at(p_pos)->get_time_wait() == 0){
						ps.at(p_pos)->fill_wait_time();
						ps.at(p_pos)->set_sprites_num(9);
						ps.at(p_pos)->set_lifes(ps.at(p_pos)->get_lifes() - 1);
						ps.at(p_pos)->set_sound_num(2);
					}

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');




				}else
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

					//muda o som
					player->set_sound_num(0);

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

					//muda o som
					player->set_sound_num(1);

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
				for(int i = 0; i < ps.size(); i++){
					if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j() &&
						ps.at(i)->get_id() != player->get_id()){
						p_pos = i;
					}
				}

				if(p_pos == -1){
					g_map->set_map_at(player->get_i(), player->get_j(), '0');
				}

				player->set_j(player->get_j() + 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '3'){
					//Procura por jogador
					for(int i = 0; i < ps.size(); i++){
						if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j()
						&& ps.at(i)->get_id() != player->get_id()){
							p_pos = i;
						}
					}

					//Colisão com outro jogador
					if(player->get_super_force() > 0 && ps.at(p_pos)->get_super_force() == 0 &&
						ps.at(p_pos)->get_time_wait() == 0){
						ps.at(p_pos)->fill_wait_time();
						ps.at(p_pos)->set_sprites_num(9);
						ps.at(p_pos)->set_lifes(ps.at(p_pos)->get_lifes() - 1);
						ps.at(p_pos)->set_sound_num(2);
					}

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');



				}else
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

					//muda o som
					player->set_sound_num(0);

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

					//muda o som
					player->set_sound_num(1);

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
				for(int i = 0; i < ps.size(); i++){
					if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j() &&
						ps.at(i)->get_id() != player->get_id()){
						p_pos = i;
					}
				}

				if(p_pos == -1){
					g_map->set_map_at(player->get_i(), player->get_j(), '0');
				}

				player->set_j(player->get_j() - 1);

				if(g_map->get_map_at(player->get_i(), player->get_j()) == '3'){
					//Procura por jogador
					for(int i = 0; i < ps.size(); i++){
						if(ps.at(i)->get_i() == player->get_i() && ps.at(i)->get_j() == player->get_j()
						&& ps.at(i)->get_id() != player->get_id()){
							p_pos = i;
						}
					}


					//Colisão com outro jogador
					if(player->get_super_force() > 0 && ps.at(p_pos)->get_super_force() == 0 &&
						ps.at(p_pos)->get_time_wait() == 0){
						ps.at(p_pos)->fill_wait_time();
						ps.at(p_pos)->set_sprites_num(9);
						ps.at(p_pos)->set_lifes(ps.at(p_pos)->get_lifes() - 1);
						ps.at(p_pos)->set_sound_num(2);
					}

					//Altera os valores do mapa
					g_map->set_map_at(player->get_i(), player->get_j(), '3');

				}else
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

					//muda o som
					player->set_sound_num(0);

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

					//muda o som
					player->set_sound_num(1);

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

//Manipula o vetor de string para cada player
void player_handler(Socket player_scoket, int player_id, vector<char*>* buffer){
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
	string map_names[] = {"../res/maps/map1.txt","../res/maps/map2.txt","../res/maps/map3.txt"};
	vector<Map*> maps;
	for(int i = 0; i < 3; i++){
		Map* m = new Map(224, 248, map_names[i]);
		maps.push_back(m);
	}

	//Jogadores
	vector<Player*> players;
	vector<Player*> tmp;

	//Guarda características de jogadores
	for(int i = 0; i < player_scoket->size(); i++){
		Player* player = new Player(0, 0, i);
		players.push_back(player);
	}

	vector<pair<int, int>> wins;
	for(int i = 0; i < player_scoket->size(); i++){
		wins.push_back(make_pair(i, 0));
	}

	//Mensagens
	string msg;
	char* buffer_dots = new char[2048];
	char* buffer_info = new char[2048];

	//Remove os jogadores restantes
	for(int g = 0; g < 3; g++){
		for(int i = players.size(); i < 4; i++){
			maps.at(g)->set_map_at(maps.at(g)->get_initial_player_pos()->at(i).first,
				maps.at(g)->get_initial_player_pos()->at(i).second, '0');
		}
	}

	//Cria um buffer pra cada player
	for(int i = 0; i < players.size(); i++){
		char* b = new char[10];
		buffers->push_back(b);
	}

	//Cria uma thread pra cada player
	for(int i = 0; i < player_scoket->size(); i++){
		thread* new_player_handler = new thread(player_handler, player_scoket->at(i), i, buffers);
		threads->push_back(new_player_handler);
	}

	//Envia o número de jogadores na partida
	msg = to_string(player_scoket->size());
	memset(buffer_dots, '\0', 10);
	msg.copy(buffer_dots, 10, 0);

	for(int i = 0; i < player_scoket->size(); i++){
		player_scoket->at(i).send(1, buffer_dots, 10);
	}

	//############## GAME SERVER #########
	for(int g = 0; g < 3; g++){

		//Define informações iniciais do player
		for(int i = 0; i < players.size(); i++){
			players.at(i)->set_eaten_biscuits(0);
			pair<int, int> pos = maps.at(g)->get_initial_player_pos()->at(i);
			players.at(i)->set_i(pos.first);
			players.at(i)->set_j(pos.second);
		}

		//Envia o mapa a ser usado
		msg = to_string(g);
		memset(buffer_dots, '\0', 10);
		msg.copy(buffer_dots, 10, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_dots, 10);
		}

		//Envia status

		//Envia status 1
		msg = to_string(1);
		memset(buffer_dots, '\0', 2048);
		msg.copy(buffer_dots, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_dots, 2048);
		}

		this_thread::sleep_for(chrono::milliseconds(1000));

		//Envia status 2
		msg = to_string(2);
		memset(buffer_dots, '\0', 2048);
		msg.copy(buffer_dots, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_dots, 2048);
		}

		this_thread::sleep_for(chrono::milliseconds(1000));

		//Envia status 3
		msg = to_string(3);
		memset(buffer_dots, '\0', 2048);
		msg.copy(buffer_dots, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_dots, 2048);
		}

		this_thread::sleep_for(chrono::milliseconds(1000));

		//Envia status 4
		msg = to_string(4);
		memset(buffer_dots, '\0', 2048);
		msg.copy(buffer_dots, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_dots, 2048);
		}

		this_thread::sleep_for(chrono::milliseconds(1000));

		map<pair<int,int>,char>::iterator it;
		while(maps.at(g)->get_biscuits()->size() != 0){
			//Para cada jogador, realiza o processamento
			//Reseta os sons

			for(int i = 0; i < players.size(); i++){
				players.at(i)->set_sound_num(-1);
			}

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

				if(players.at(i)->get_lifes() > 0){
					if(players.at(i)->get_time_wait() == 0){
						switch(players.at(i)->get_direction()){
							case 0:
								switch(players.at(i)->get_desired_direction()){
									case 0:
										collide(players.at(i), maps.at(g), 0, true, players);
									break;

									case 1:
										if(!collide(players.at(i), maps.at(g), 1, false, players)){
											collide(players.at(i), maps.at(g), 0, true, players);
										}
									break;

									case 2:
										if(!collide(players.at(i), maps.at(g), 2, false, players)){
											collide(players.at(i), maps.at(g), 0, true, players);
										}
									break;

									case 3:
										if(!collide(players.at(i), maps.at(g), 3, false, players)){
											collide(players.at(i), maps.at(g), 0, true, players);
										}
									break;
								}
							break;

							//############################## 1 #################################
							case 1:
								switch(players.at(i)->get_desired_direction()){
									case 0:
										if(!collide(players.at(i), maps.at(g), 0, false, players)){
											collide(players.at(i), maps.at(g), 1, true, players);
										}
									break;

									case 1:
										collide(players.at(i), maps.at(g), 1, true, players);
									break;

									case 2:
										if(!collide(players.at(i), maps.at(g), 2, false, players)){
											collide(players.at(i), maps.at(g), 1, true, players);
										}
									break;

									case 3:
										if(!collide(players.at(i), maps.at(g), 3, false, players)){
											collide(players.at(i), maps.at(g), 1, true, players);
										}
									break;
								}
							break;

							case 2:
								switch(players.at(i)->get_desired_direction()){
									case 0:
										if(!collide(players.at(i), maps.at(g), 0, false, players)){
											collide(players.at(i), maps.at(g), 2, true, players);
										}
									break;

									case 1:
										if(!collide(players.at(i), maps.at(g), 1, false, players)){
											collide(players.at(i), maps.at(g), 2, true, players);
										}
									break;

									case 2:
										collide(players.at(i), maps.at(g), 2, true, players);
									break;

									case 3:
										if(!collide(players.at(i), maps.at(g), 3, false, players)){
											collide(players.at(i), maps.at(g), 2, true, players);
										}
									break;
								}
							break;

							case 3:
								switch(players.at(i)->get_desired_direction()){
									case 0:
										if(!collide(players.at(i), maps.at(g), 0, false, players)){
											collide(players.at(i), maps.at(g), 3, true, players);
										}
									break;

									case 1:
										if(!collide(players.at(i), maps.at(g), 1, false, players)){
											collide(players.at(i), maps.at(g), 3, true, players);
										}
									break;

									case 2:
										if(!collide(players.at(i), maps.at(g), 2, false, players)){
											collide(players.at(i), maps.at(g), 3, true, players);
										}
									break;

									case 3:
										collide(players.at(i), maps.at(g), 3, true, players);
									break;
								}
							break;
						}
					}else{
						//Verificar a treta aqui
						if(players.at(i)->get_sprites_num() == 9){
							players.at(i)->set_sprites_num(10);
						}else
						if(players.at(i)->get_sprites_num() == 10){
							players.at(i)->set_sprites_num(11);
						}else
						if(players.at(i)->get_sprites_num() == 11){
							players.at(i)->set_sprites_num(12);
						}else
						if(players.at(i)->get_sprites_num() == 12){
							players.at(i)->set_sprites_num(13);
						}else
						if(players.at(i)->get_sprites_num() == 13){
							players.at(i)->set_sprites_num(14);
						}else
						if(players.at(i)->get_sprites_num() == 14){
							players.at(i)->set_sprites_num(15);
						}else
						if(players.at(i)->get_sprites_num() == 15){
							players.at(i)->set_sprites_num(16);
						}else
						if(players.at(i)->get_sprites_num() == 16){
							players.at(i)->set_sprites_num(17);
						}else
						if(players.at(i)->get_sprites_num() == 17){
							players.at(i)->set_sprites_num(18);
						}else
						if(players.at(i)->get_sprites_num() == 18){
							players.at(i)->set_sprites_num(19);
						}else
						if(players.at(i)->get_sprites_num() == 19){
							players.at(i)->set_sprites_num(20);
						}else
						if(players.at(i)->get_sprites_num() == 20){
							players.at(i)->set_sprites_num(20);
						}

						players.at(i)->decrease_wait_time();

						if(players.at(i)->get_time_wait() == 0){
							players.at(i)->set_sprites_num(0);
						}
					}
				}else{
					players.at(i)->set_sprites_num(20);
				}
			}

			//Mensagem já pode ser gerada
			//Envia os biscuits e super biscuits
			msg = "";
			for(it = maps.at(g)->get_biscuits()->begin(); it != maps.at(g)->get_biscuits()->end(); it++){
				msg += string(to_string(it->first.first) + "x" + to_string(it->first.second) + ";");
			}

			for(it = maps.at(g)->get_s_biscuits()->begin(); it != maps.at(g)->get_s_biscuits()->end(); it++){
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
				to_string(players.at(i)->get_sound_num()) + "|" + to_string(players.at(i)->get_eaten_biscuits()) + "|" +
				to_string(players.at(i)->get_item()) + "|;");
			}


			memset(buffer_info, '\0', 2048);
			msg.copy(buffer_info, 2048, 0);

			for(int i = 0; i < player_scoket->size(); i++){
				player_scoket->at(i).send(1, buffer_info, 2048);
			}

			this_thread::sleep_for(chrono::milliseconds(20));

		}

		tmp.clear();

		for(int i = 0; i < players.size(); i++){
			Player* p = new Player(*(players.at(i)));
			tmp.push_back(p);
		}
		//Ordena os jogadores
		sort(tmp.begin(), tmp.end(), player_sort);

		//Aumenta número de vitórias
		wins.at(tmp.at(0)->get_id()).second += 1;

		//Envia status
		msg = "EOM";
		memset(buffer_dots, '\0', 2048);
		msg.copy(buffer_dots, 2048, 0);

		for(int i = 0; i < player_scoket->size(); i++){
			player_scoket->at(i).send(1, buffer_dots, 2048);
		}
	}

	//################## END FOR G LOOP ##########
	sort(wins.begin(), wins.end(), wins_sort);

	//Envia EOG
	msg = "EOG";
	memset(buffer_dots, '\0', 10);
	msg.copy(buffer_dots, 10, 0);

	for(int i = 0; i < player_scoket->size(); i++){
		player_scoket->at(i).send(1, buffer_dots, 10);
	}

	//Envia vencedor
	msg = to_string(wins.at(0).first);
	memset(buffer_dots, '\0', 10);
	msg.copy(buffer_dots, 10, 0);

	for(int i = 0; i < player_scoket->size(); i++){
		player_scoket->at(i).send(1, buffer_dots, 10);
	}

	//Encerra as threads acima
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
		for(int i = 0; i < num_players; i++){
			//mt.lock();
			server_socket.accept();
			players->push_back(server_socket);
			//mt.unlock();
		}

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

	thread new_receptionist(players_receptionist, ip, port, num_players);
	new_receptionist.join();

	return 0;
}
