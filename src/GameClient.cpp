#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <string.h>
#include <vector>
#include <utility>
#include "Socket.hpp"
#include "Player.hpp"
#include "Ghost.hpp"

using namespace std;
using namespace sf;

mutex mt;

void thread_snd(Socket client_game, bool* has_finish, RenderWindow* window){
	cout << "Thread de envio iniciado com sucesso!" << endl;

	char* buffer = new char[10];
	string msg;

	cout << "Bem vindo, digite sua mensagem e pressione enter para enviar" << endl;
	Event event;
//	this_thread::sleep_for(chrono::milliseconds(1000));

	while (window->isOpen()){
		while (window->pollEvent(event)){
			if (event.type == Event::KeyPressed){
				memset(buffer, '\0', 10);
				msg = to_string(event.key.code);
				msg.copy(buffer, 10, 0);
				client_game.send(0, buffer, 10);

				if(event.key.code == 36){
					window->close();
					break;
				}
			}
		}
	}
}

void thread_rcv(Socket client_game, bool* has_finish){

	cout << "Thread de recebimento inciada com sucesso!" << endl;
	RenderWindow* window = new RenderWindow(VideoMode(400, 300), "Pac-Doni");

	cout << "Iniciando thread de envio..." << endl;
	thread* send = new thread(thread_snd, client_game, has_finish, window);

	char* buffer = new char[2048];
	string msg;
	string word;
	string b_num;
	int pos, apos, xpos;
	vector<pair<int,int>> biscuits;
	vector<pair<int,int>> s_biscuits;
	vector<Player> players;
	vector<Ghost> ghosts;
	vector<string> pl_info;
	vector<int> info;
	pair<int, int> b_pos;

	Texture maze_texture;
	maze_texture.loadFromFile("../res/sprites/map_1.png");
	maze_texture.setSmooth(false);

	Texture game_s_texture;
	game_s_texture.loadFromFile("../res/sprites/game_screen.png");
	game_s_texture.setSmooth(false);

	Texture biscuit_texture;
	biscuit_texture.loadFromFile("../res/sprites/biscuit.png");
	biscuit_texture.setSmooth(false);

	Texture s_biscuit_texture;
	s_biscuit_texture.loadFromFile("../res/sprites/super_biscuit.png");
	s_biscuit_texture.setSmooth(false);

	Texture pac_texture[21][4];
	pac_texture[0][0].loadFromFile("../res/sprites/pac_1_1.png");
	pac_texture[0][0].setSmooth(false);
	pac_texture[1][0].loadFromFile("../res/sprites/pac_1_d_1.png");
	pac_texture[1][0].setSmooth(false);
	pac_texture[2][0].loadFromFile("../res/sprites/pac_1_d_2.png");
	pac_texture[2][0].setSmooth(false);
	pac_texture[3][0].loadFromFile("../res/sprites/pac_1_u_1.png");
	pac_texture[3][0].setSmooth(false);
	pac_texture[4][0].loadFromFile("../res/sprites/pac_1_u_2.png");
	pac_texture[4][0].setSmooth(false);
	pac_texture[5][0].loadFromFile("../res/sprites/pac_1_r_1.png");
	pac_texture[5][0].setSmooth(false);
	pac_texture[6][0].loadFromFile("../res/sprites/pac_1_r_2.png");
	pac_texture[6][0].setSmooth(false);
	pac_texture[7][0].loadFromFile("../res/sprites/pac_1_l_1.png");
	pac_texture[7][0].setSmooth(false);
	pac_texture[8][0].loadFromFile("../res/sprites/pac_1_l_2.png");
	pac_texture[8][0].setSmooth(false);
	pac_texture[9][0].loadFromFile("../res/sprites/pac_1_k_1.png");
	pac_texture[9][0].setSmooth(false);
	pac_texture[10][0].loadFromFile("../res/sprites/pac_1_k_2.png");
	pac_texture[10][0].setSmooth(false);
	pac_texture[11][0].loadFromFile("../res/sprites/pac_1_k_3.png");
	pac_texture[11][0].setSmooth(false);
	pac_texture[12][0].loadFromFile("../res/sprites/pac_1_k_4.png");
	pac_texture[12][0].setSmooth(false);
	pac_texture[13][0].loadFromFile("../res/sprites/pac_1_k_5.png");
	pac_texture[13][0].setSmooth(false);
	pac_texture[14][0].loadFromFile("../res/sprites/pac_1_k_6.png");
	pac_texture[14][0].setSmooth(false);
	pac_texture[15][0].loadFromFile("../res/sprites/pac_1_k_7.png");
	pac_texture[15][0].setSmooth(false);
	pac_texture[16][0].loadFromFile("../res/sprites/pac_1_k_8.png");
	pac_texture[16][0].setSmooth(false);
	pac_texture[17][0].loadFromFile("../res/sprites/pac_1_k_9.png");
	pac_texture[17][0].setSmooth(false);
	pac_texture[18][0].loadFromFile("../res/sprites/pac_1_k_10.png");
	pac_texture[18][0].setSmooth(false);
	pac_texture[19][0].loadFromFile("../res/sprites/pac_1_k_11.png");
	pac_texture[19][0].setSmooth(false);
	pac_texture[20][0].loadFromFile("../res/sprites/pac_1_k_12.png");
	pac_texture[20][0].setSmooth(false);

	pac_texture[0][1].loadFromFile("../res/sprites/pac_2_1.png");
	pac_texture[0][1].setSmooth(false);
	pac_texture[1][1].loadFromFile("../res/sprites/pac_2_d_1.png");
	pac_texture[1][1].setSmooth(false);
	pac_texture[2][1].loadFromFile("../res/sprites/pac_2_d_2.png");
	pac_texture[2][1].setSmooth(false);
	pac_texture[3][1].loadFromFile("../res/sprites/pac_2_u_1.png");
	pac_texture[3][1].setSmooth(false);
	pac_texture[4][1].loadFromFile("../res/sprites/pac_2_u_2.png");
	pac_texture[4][1].setSmooth(false);
	pac_texture[5][1].loadFromFile("../res/sprites/pac_2_r_1.png");
	pac_texture[5][1].setSmooth(false);
	pac_texture[6][1].loadFromFile("../res/sprites/pac_2_r_2.png");
	pac_texture[6][1].setSmooth(false);
	pac_texture[7][1].loadFromFile("../res/sprites/pac_2_l_1.png");
	pac_texture[7][1].setSmooth(false);
	pac_texture[8][1].loadFromFile("../res/sprites/pac_2_l_2.png");
	pac_texture[8][1].setSmooth(false);
	pac_texture[9][1].loadFromFile("../res/sprites/pac_2_k_1.png");
	pac_texture[9][1].setSmooth(false);
	pac_texture[10][1].loadFromFile("../res/sprites/pac_2_k_2.png");
	pac_texture[10][1].setSmooth(false);
	pac_texture[11][1].loadFromFile("../res/sprites/pac_2_k_3.png");
	pac_texture[11][1].setSmooth(false);
	pac_texture[12][1].loadFromFile("../res/sprites/pac_2_k_4.png");
	pac_texture[12][1].setSmooth(false);
	pac_texture[13][1].loadFromFile("../res/sprites/pac_2_k_5.png");
	pac_texture[13][1].setSmooth(false);
	pac_texture[14][1].loadFromFile("../res/sprites/pac_2_k_6.png");
	pac_texture[14][1].setSmooth(false);
	pac_texture[15][1].loadFromFile("../res/sprites/pac_2_k_7.png");
	pac_texture[15][1].setSmooth(false);
	pac_texture[16][1].loadFromFile("../res/sprites/pac_2_k_8.png");
	pac_texture[16][1].setSmooth(false);
	pac_texture[17][1].loadFromFile("../res/sprites/pac_2_k_9.png");
	pac_texture[17][1].setSmooth(false);
	pac_texture[18][1].loadFromFile("../res/sprites/pac_2_k_10.png");
	pac_texture[18][1].setSmooth(false);
	pac_texture[19][1].loadFromFile("../res/sprites/pac_2_k_11.png");
	pac_texture[19][1].setSmooth(false);
	pac_texture[20][1].loadFromFile("../res/sprites/pac_2_k_12.png");
	pac_texture[20][1].setSmooth(false);

	pac_texture[0][2].loadFromFile("../res/sprites/pac_3_1.png");
	pac_texture[0][2].setSmooth(false);
	pac_texture[1][2].loadFromFile("../res/sprites/pac_3_d_1.png");
	pac_texture[1][2].setSmooth(false);
	pac_texture[2][2].loadFromFile("../res/sprites/pac_3_d_2.png");
	pac_texture[2][2].setSmooth(false);
	pac_texture[3][2].loadFromFile("../res/sprites/pac_3_u_1.png");
	pac_texture[3][2].setSmooth(false);
	pac_texture[4][2].loadFromFile("../res/sprites/pac_3_u_2.png");
	pac_texture[4][2].setSmooth(false);
	pac_texture[5][2].loadFromFile("../res/sprites/pac_3_r_1.png");
	pac_texture[5][2].setSmooth(false);
	pac_texture[6][2].loadFromFile("../res/sprites/pac_3_r_2.png");
	pac_texture[6][2].setSmooth(false);
	pac_texture[7][2].loadFromFile("../res/sprites/pac_3_l_1.png");
	pac_texture[7][2].setSmooth(false);
	pac_texture[8][2].loadFromFile("../res/sprites/pac_3_l_2.png");
	pac_texture[8][2].setSmooth(false);
	pac_texture[9][2].loadFromFile("../res/sprites/pac_3_k_1.png");
	pac_texture[9][2].setSmooth(false);
	pac_texture[10][2].loadFromFile("../res/sprites/pac_3_k_2.png");
	pac_texture[10][2].setSmooth(false);
	pac_texture[11][2].loadFromFile("../res/sprites/pac_3_k_3.png");
	pac_texture[11][2].setSmooth(false);
	pac_texture[12][2].loadFromFile("../res/sprites/pac_3_k_4.png");
	pac_texture[12][2].setSmooth(false);
	pac_texture[13][2].loadFromFile("../res/sprites/pac_3_k_5.png");
	pac_texture[13][2].setSmooth(false);
	pac_texture[14][2].loadFromFile("../res/sprites/pac_3_k_6.png");
	pac_texture[14][2].setSmooth(false);
	pac_texture[15][2].loadFromFile("../res/sprites/pac_3_k_7.png");
	pac_texture[15][2].setSmooth(false);
	pac_texture[16][2].loadFromFile("../res/sprites/pac_3_k_8.png");
	pac_texture[16][2].setSmooth(false);
	pac_texture[17][2].loadFromFile("../res/sprites/pac_3_k_9.png");
	pac_texture[17][2].setSmooth(false);
	pac_texture[18][2].loadFromFile("../res/sprites/pac_3_k_10.png");
	pac_texture[18][2].setSmooth(false);
	pac_texture[19][2].loadFromFile("../res/sprites/pac_3_k_11.png");
	pac_texture[19][2].setSmooth(false);
	pac_texture[20][2].loadFromFile("../res/sprites/pac_3_k_12.png");
	pac_texture[20][2].setSmooth(false);

	pac_texture[0][3].loadFromFile("../res/sprites/pac_4_1.png");
	pac_texture[0][3].setSmooth(false);
	pac_texture[1][3].loadFromFile("../res/sprites/pac_4_d_1.png");
	pac_texture[1][3].setSmooth(false);
	pac_texture[2][3].loadFromFile("../res/sprites/pac_4_d_2.png");
	pac_texture[2][3].setSmooth(false);
	pac_texture[3][3].loadFromFile("../res/sprites/pac_4_u_1.png");
	pac_texture[3][3].setSmooth(false);
	pac_texture[4][3].loadFromFile("../res/sprites/pac_4_u_2.png");
	pac_texture[4][3].setSmooth(false);
	pac_texture[5][3].loadFromFile("../res/sprites/pac_4_r_1.png");
	pac_texture[5][3].setSmooth(false);
	pac_texture[6][3].loadFromFile("../res/sprites/pac_4_r_2.png");
	pac_texture[6][3].setSmooth(false);
	pac_texture[7][3].loadFromFile("../res/sprites/pac_4_l_1.png");
	pac_texture[7][3].setSmooth(false);
	pac_texture[8][3].loadFromFile("../res/sprites/pac_4_l_2.png");
	pac_texture[8][3].setSmooth(false);
	pac_texture[9][3].loadFromFile("../res/sprites/pac_4_k_1.png");
	pac_texture[9][3].setSmooth(false);
	pac_texture[10][3].loadFromFile("../res/sprites/pac_4_k_2.png");
	pac_texture[10][3].setSmooth(false);
	pac_texture[11][3].loadFromFile("../res/sprites/pac_4_k_3.png");
	pac_texture[11][3].setSmooth(false);
	pac_texture[12][3].loadFromFile("../res/sprites/pac_4_k_4.png");
	pac_texture[12][3].setSmooth(false);
	pac_texture[13][3].loadFromFile("../res/sprites/pac_4_k_5.png");
	pac_texture[13][3].setSmooth(false);
	pac_texture[14][3].loadFromFile("../res/sprites/pac_4_k_6.png");
	pac_texture[14][3].setSmooth(false);
	pac_texture[15][3].loadFromFile("../res/sprites/pac_4_k_7.png");
	pac_texture[15][3].setSmooth(false);
	pac_texture[16][3].loadFromFile("../res/sprites/pac_4_k_8.png");
	pac_texture[16][3].setSmooth(false);
	pac_texture[17][3].loadFromFile("../res/sprites/pac_4_k_9.png");
	pac_texture[17][3].setSmooth(false);
	pac_texture[18][3].loadFromFile("../res/sprites/pac_4_k_10.png");
	pac_texture[18][3].setSmooth(false);
	pac_texture[19][3].loadFromFile("../res/sprites/pac_4_k_11.png");
	pac_texture[19][3].setSmooth(false);
	pac_texture[20][3].loadFromFile("../res/sprites/pac_4_k_12.png");
	pac_texture[20][3].setSmooth(false);

	Texture lifes_texture[4];
	lifes_texture[0].loadFromFile("../res/sprites/life_1.png");
	lifes_texture[1].loadFromFile("../res/sprites/life_2.png");
	lifes_texture[2].loadFromFile("../res/sprites/life_3.png");
	lifes_texture[3].loadFromFile("../res/sprites/life_4.png");

	Texture numbers_texture[10];
	numbers_texture[0].loadFromFile("../res/sprites/num_0.png");
	numbers_texture[1].loadFromFile("../res/sprites/num_1.png");
	numbers_texture[2].loadFromFile("../res/sprites/num_2.png");
	numbers_texture[3].loadFromFile("../res/sprites/num_3.png");
	numbers_texture[4].loadFromFile("../res/sprites/num_4.png");
	numbers_texture[5].loadFromFile("../res/sprites/num_5.png");
	numbers_texture[6].loadFromFile("../res/sprites/num_6.png");
	numbers_texture[7].loadFromFile("../res/sprites/num_7.png");
	numbers_texture[8].loadFromFile("../res/sprites/num_8.png");
	numbers_texture[9].loadFromFile("../res/sprites/num_9.png");

	Texture ghost_texture[19][4];
	ghost_texture[0][0].loadFromFile("../res/sprites/ghost_red_u_1.png");
	ghost_texture[1][0].loadFromFile("../res/sprites/ghost_red_u_2.png");
	ghost_texture[2][0].loadFromFile("../res/sprites/ghost_red_d_1.png");
	ghost_texture[3][0].loadFromFile("../res/sprites/ghost_red_d_2.png");
	ghost_texture[4][0].loadFromFile("../res/sprites/ghost_red_l_1.png");
	ghost_texture[5][0].loadFromFile("../res/sprites/ghost_red_l_2.png");
	ghost_texture[6][0].loadFromFile("../res/sprites/ghost_red_r_1.png");
	ghost_texture[7][0].loadFromFile("../res/sprites/ghost_red_r_2.png");
	ghost_texture[8][0].loadFromFile("../res/sprites/ghost_red_b_1.png");
	ghost_texture[9][0].loadFromFile("../res/sprites/ghost_red_b_2.png");
	ghost_texture[10][0].loadFromFile("../res/sprites/ghost_red_b_3.png");
	ghost_texture[11][0].loadFromFile("../res/sprites/ghost_s_1_1.png");
	ghost_texture[12][0].loadFromFile("../res/sprites/ghost_s_1_2.png");
	ghost_texture[13][0].loadFromFile("../res/sprites/ghost_s_2_1.png");
	ghost_texture[14][0].loadFromFile("../res/sprites/ghost_s_2_2.png");
	ghost_texture[15][0].loadFromFile("../res/sprites/ghost_k_d.png");
	ghost_texture[16][0].loadFromFile("../res/sprites/ghost_k_l.png");
	ghost_texture[17][0].loadFromFile("../res/sprites/ghost_k_r.png");
	ghost_texture[18][0].loadFromFile("../res/sprites/ghost_k_u.png");

	ghost_texture[0][1].loadFromFile("../res/sprites/ghost_blue_u_1.png");
	ghost_texture[1][1].loadFromFile("../res/sprites/ghost_blue_u_2.png");
	ghost_texture[2][1].loadFromFile("../res/sprites/ghost_blue_d_1.png");
	ghost_texture[3][1].loadFromFile("../res/sprites/ghost_blue_d_2.png");
	ghost_texture[4][1].loadFromFile("../res/sprites/ghost_blue_l_1.png");
	ghost_texture[5][1].loadFromFile("../res/sprites/ghost_blue_l_2.png");
	ghost_texture[6][1].loadFromFile("../res/sprites/ghost_blue_r_1.png");
	ghost_texture[7][1].loadFromFile("../res/sprites/ghost_blue_r_2.png");
	ghost_texture[8][1].loadFromFile("../res/sprites/ghost_blue_b_1.png");
	ghost_texture[9][1].loadFromFile("../res/sprites/ghost_blue_b_2.png");
	ghost_texture[10][1].loadFromFile("../res/sprites/ghost_blue_b_3.png");
	ghost_texture[11][1].loadFromFile("../res/sprites/ghost_s_1_1.png");
	ghost_texture[12][1].loadFromFile("../res/sprites/ghost_s_1_2.png");
	ghost_texture[13][1].loadFromFile("../res/sprites/ghost_s_2_1.png");
	ghost_texture[14][1].loadFromFile("../res/sprites/ghost_s_2_2.png");
	ghost_texture[15][1].loadFromFile("../res/sprites/ghost_k_d.png");
	ghost_texture[16][1].loadFromFile("../res/sprites/ghost_k_l.png");
	ghost_texture[17][1].loadFromFile("../res/sprites/ghost_k_r.png");
	ghost_texture[18][1].loadFromFile("../res/sprites/ghost_k_u.png");

	ghost_texture[0][2].loadFromFile("../res/sprites/ghost_pink_u_1.png");
	ghost_texture[1][2].loadFromFile("../res/sprites/ghost_pink_u_2.png");
	ghost_texture[2][2].loadFromFile("../res/sprites/ghost_pink_d_1.png");
	ghost_texture[3][2].loadFromFile("../res/sprites/ghost_pink_d_2.png");
	ghost_texture[4][2].loadFromFile("../res/sprites/ghost_pink_l_1.png");
	ghost_texture[5][2].loadFromFile("../res/sprites/ghost_pink_l_2.png");
	ghost_texture[6][2].loadFromFile("../res/sprites/ghost_pink_r_1.png");
	ghost_texture[7][2].loadFromFile("../res/sprites/ghost_pink_r_2.png");
	ghost_texture[8][2].loadFromFile("../res/sprites/ghost_pink_b_1.png");
	ghost_texture[9][2].loadFromFile("../res/sprites/ghost_pink_b_2.png");
	ghost_texture[10][2].loadFromFile("../res/sprites/ghost_pink_b_3.png");
	ghost_texture[11][2].loadFromFile("../res/sprites/ghost_s_1_1.png");
	ghost_texture[12][2].loadFromFile("../res/sprites/ghost_s_1_2.png");
	ghost_texture[13][2].loadFromFile("../res/sprites/ghost_s_2_1.png");
	ghost_texture[14][2].loadFromFile("../res/sprites/ghost_s_2_2.png");
	ghost_texture[15][2].loadFromFile("../res/sprites/ghost_k_d.png");
	ghost_texture[16][2].loadFromFile("../res/sprites/ghost_k_l.png");
	ghost_texture[17][2].loadFromFile("../res/sprites/ghost_k_r.png");
	ghost_texture[18][2].loadFromFile("../res/sprites/ghost_k_u.png");

	ghost_texture[0][3].loadFromFile("../res/sprites/ghost_yellow_u_1.png");
	ghost_texture[1][3].loadFromFile("../res/sprites/ghost_yellow_u_2.png");
	ghost_texture[2][3].loadFromFile("../res/sprites/ghost_yellow_d_1.png");
	ghost_texture[3][3].loadFromFile("../res/sprites/ghost_yellow_d_2.png");
	ghost_texture[4][3].loadFromFile("../res/sprites/ghost_yellow_l_1.png");
	ghost_texture[5][3].loadFromFile("../res/sprites/ghost_yellow_l_2.png");
	ghost_texture[6][3].loadFromFile("../res/sprites/ghost_yellow_r_1.png");
	ghost_texture[7][3].loadFromFile("../res/sprites/ghost_yellow_r_2.png");
	ghost_texture[8][3].loadFromFile("../res/sprites/ghost_yellow_b_1.png");
	ghost_texture[9][3].loadFromFile("../res/sprites/ghost_yellow_b_2.png");
	ghost_texture[10][3].loadFromFile("../res/sprites/ghost_yellow_b_3.png");
	ghost_texture[11][3].loadFromFile("../res/sprites/ghost_s_1_1.png");
	ghost_texture[12][3].loadFromFile("../res/sprites/ghost_s_1_2.png");
	ghost_texture[13][3].loadFromFile("../res/sprites/ghost_s_2_1.png");
	ghost_texture[14][3].loadFromFile("../res/sprites/ghost_s_2_2.png");
	ghost_texture[15][3].loadFromFile("../res/sprites/ghost_k_d.png");
	ghost_texture[16][3].loadFromFile("../res/sprites/ghost_k_l.png");
	ghost_texture[17][3].loadFromFile("../res/sprites/ghost_k_r.png");
	ghost_texture[18][3].loadFromFile("../res/sprites/ghost_k_u.png");

	Texture letter_texture;
	letter_texture.loadFromFile("../res/sprites/letter_X.png");

	Sprite maze;
	maze.setTexture(maze_texture);
	maze.setPosition(Vector2f(150, 26));

	Sprite game_s;
	game_s.setTexture(game_s_texture);

	Sprite biscuit;
	biscuit.setTexture(biscuit_texture);

	Sprite s_biscuit;
	s_biscuit.setTexture(s_biscuit_texture);

	Sprite pac[21][4];
	for(int i = 0; i < 21; i++){
		for(int j = 0; j < 4; j++){
			pac[i][j].setTexture(pac_texture[i][j]);
		}
	}

	Sprite lifes[4];
	for(int i = 0; i < 4; i++){
		lifes[i].setTexture(lifes_texture[i]);
	}

	Sprite numbers[10];
	for(int i = 0; i < 10; i++){
		numbers[i].setTexture(numbers_texture[i]);
	}

	Sprite ghost[19][4];
	for(int i = 0; i < 21; i++){
		for(int j = 0; j < 4; j++){
			ghost[i][j].setTexture(ghost_texture[i][j]);
		}
	}

	Sprite letter;
	letter.setTexture(letter_texture);

	while (window->isOpen()){

		//BISCUITS
		memset(buffer, '\0', 2048);
		client_game.recv(0, buffer, 2048);
		msg = string(buffer);

		//Quebra a mensegem para encontrar todos os pontos
		apos = 0;
		biscuits.clear();
		s_biscuits.clear();

		while(apos < msg.size()){
			pos = msg.find(';', apos);
			word = msg.substr(apos, pos);
			xpos = word.find_first_of('x');

			if(word[0] != 'S'){
				b_pos.first = stoi(word.substr(0,xpos));
				b_pos.second = stoi(word.substr(xpos + 1, word.size() - xpos + 1));
				biscuits.push_back(b_pos);
			}else{
				b_pos.first = stoi(word.substr(1,xpos));
				b_pos.second = stoi(word.substr(xpos + 1, word.size() - xpos + 1));
				s_biscuits.push_back(b_pos);
			}

			apos = pos + 1;
		}

		//JOGADOR
		memset(buffer, '\0', 2048);
		client_game.recv(0, buffer, 2048);
		msg = string(buffer);

		//Quebra a mensegem para encontrar todos os pontos
		apos = 0;
		pl_info.clear();
		players.clear();

		while(apos < msg.size()){
			pos = msg.find(';', apos);
			word = msg.substr(apos, pos - apos);
			pl_info.push_back(word);
			apos = pos + 1;
		}

		for(int i = 0; i < pl_info.size(); i++){
			apos = 0;
			info.clear();

			while(apos < pl_info.at(i).size()){
				pos = pl_info.at(i).find('|', apos);
				word = pl_info.at(i).substr(apos, pos - apos);
				info.push_back(stoi(word));
				apos = pos + 1;
			}

			Player p(info.at(0), info.at(1));
			p.set_sprites_num(info.at(2));
			p.set_lifes(info.at(3));
			p.set_sound_num(info.at(4));
			p.set_eaten_biscuits(info.at(5));
			p.set_item(info.at(6));

			players.push_back(p);
		}

		//FANTASMAS
		memset(buffer, '\0', 2048);
		client_game.recv(0, buffer, 2048);
		msg = string(buffer);

		//Quebra a mensegem para encontrar todos os pontos
		apos = 0;
		pl_info.clear();
		ghosts.clear();

		while(apos < msg.size()){
			pos = msg.find(';', apos);
			word = msg.substr(apos, pos - apos);
			pl_info.push_back(word);
			apos = pos + 1;
		}

		for(int i = 0; i < pl_info.size(); i++){
			apos = 0;
			info.clear();

			while(apos < pl_info.at(i).size()){
				pos = pl_info.at(i).find('|', apos);
				word = pl_info.at(i).substr(apos, pos - apos);
				info.push_back(stoi(word));
				apos = pos + 1;
			}

			Ghost g(info.at(0), info.at(1));
			g.set_sprites_num(info.at(2));

			ghosts.push_back(g);
		}

        window->clear();

		//Drawn here
		window->draw(game_s);
        window->draw(maze);


		//Desenha biscuits
		for(int i = 0; i < biscuits.size(); i++){
			biscuit.setPosition(Vector2f(biscuits.at(i).second + 150, biscuits.at(i).first + 26));
			window->draw(biscuit);
		}

		//Desenha super_biscuits
		for(int i = 0; i < s_biscuits.size(); i++){
			s_biscuit.setPosition(Vector2f(s_biscuits.at(i).second + 150, s_biscuits.at(i).first + 26));
			window->draw(s_biscuit);
		}

		//Desenha playeres
		for(int i = 0; i < players.size(); i++){
			pac[players.at(i).get_sprites_num()][i].setPosition(players.at(i).get_j()
				+ 150, players.at(i).get_i() + 26);
			window->draw(pac[players.at(i).get_sprites_num()][i]);
		}

		//Desenha ghost
		for(int i = 0; i < ghosts.size(); i++){
			ghost[ghosts.at(i).get_sprites_num()][i].setPosition(ghosts.at(i).get_j()
				+ 150, ghosts.at(i).get_i() + 26);
			window->draw(ghost[ghosts.at(i).get_sprites_num()][i]);
		}

		//Desenha informações (Sprite jogador)
		for(int i = 0; i < players.size(); i++){
			pac[5][i].setPosition(25, 25 + 30 * i);
			window->draw(pac[5][i]);
		}

		//Desenha informações (X)
		for(int i = 0; i < players.size(); i++){
			letter.setPosition(42, 32 + 30 * i);
			window->draw(letter);
		}


		//Desenha informações (Número de vidas)
		for(int i = 0; i < players.size(); i++){
			for(int j = 0; j < players.at(i).get_lifes(); j++){
				lifes[i].setPosition(25 + (10 * j), 42 + (30 * i));
				window->draw(lifes[i]);
			}
		}

		for(int i = 0; i < players.size(); i++){
			b_num = to_string(players.at(i).get_eaten_biscuits());
			switch(b_num.size()){
				case 1:
					numbers[0].setPosition(51, 32 + (i * 30));
					window->draw(numbers[0]);

					numbers[0].setPosition(60, 32 + (i * 30));
					window->draw(numbers[0]);

					numbers[b_num[0] - '0'].setPosition(69, 32 + (i * 30));
					window->draw(numbers[b_num[0] - '0']);

				break;

				case 2:
					numbers[0].setPosition(51, 32 + (i * 30));
					window->draw(numbers[0]);

					numbers[b_num[0] - '0'].setPosition(60, 32 + (i * 30));
					window->draw(numbers[b_num[0] - '0']);

					numbers[b_num[1] - '0'].setPosition(69, 32 + (i * 30));
					window->draw(numbers[b_num[1] - '0']);
				break;

				case 3:
					for(int j = 0; j < b_num.size(); j++){
						numbers[b_num[j] - '0'].setPosition(51 + (9 * j), 32 + (30 * i));
						window->draw(numbers[b_num[j] - '0']);
					}
				break;
			}
		}



        window->display();
    }
	send->join();
}

int main(int argc, char **argv){
	XInitThreads();
	string ip = string(argv[1]);
	int port = atoi(argv[2]);
	bool* has_finish = new bool(false);

	//Cria um atributo
	Socket client_game(ip, port);

	//Conecta ao servidor
	cout << "Iniciando conexão..." << endl;
	if(client_game.connect() == 0){

		cout << "Iniciando thread de recebimento..." << endl;
		thread* recv = new thread(thread_rcv, client_game, has_finish);
		recv->join();

		client_game.close(0);
	}else{
		cout << "Erro ao estabelecer conexão!" << endl;
	}



	return 0;
}
