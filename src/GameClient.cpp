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

using namespace std;
using namespace sf;

mutex mt;

void thread_rcv(Socket client_game, bool* has_finish, RenderWindow* window){
	cout << "Thread de recebimento inciada com sucesso!" << endl;

	char* buffer = new char[2048];
	string msg;
	string word;
	int pos, apos, xpos;
	vector<pair<int,int>> biscuits;
	vector<pair<int,int>> s_biscuits;
	vector<Player> players;
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

	Texture pac_texture[21];
	pac_texture[0].loadFromFile("../res/sprites/pac_1_1.png");
	pac_texture[0].setSmooth(false);
	pac_texture[1].loadFromFile("../res/sprites/pac_1_d_1.png");
	pac_texture[1].setSmooth(false);
	pac_texture[2].loadFromFile("../res/sprites/pac_1_d_2.png");
	pac_texture[2].setSmooth(false);
	pac_texture[3].loadFromFile("../res/sprites/pac_1_u_1.png");
	pac_texture[3].setSmooth(false);
	pac_texture[4].loadFromFile("../res/sprites/pac_1_u_2.png");
	pac_texture[4].setSmooth(false);
	pac_texture[5].loadFromFile("../res/sprites/pac_1_r_1.png");
	pac_texture[5].setSmooth(false);
	pac_texture[6].loadFromFile("../res/sprites/pac_1_r_2.png");
	pac_texture[6].setSmooth(false);
	pac_texture[7].loadFromFile("../res/sprites/pac_1_l_1.png");
	pac_texture[7].setSmooth(false);
	pac_texture[8].loadFromFile("../res/sprites/pac_1_l_2.png");
	pac_texture[8].setSmooth(false);
	pac_texture[9].loadFromFile("../res/sprites/pac_1_k_1.png");
	pac_texture[9].setSmooth(false);
	pac_texture[10].loadFromFile("../res/sprites/pac_1_k_2.png");
	pac_texture[10].setSmooth(false);
	pac_texture[11].loadFromFile("../res/sprites/pac_1_k_3.png");
	pac_texture[11].setSmooth(false);
	pac_texture[12].loadFromFile("../res/sprites/pac_1_k_4.png");
	pac_texture[12].setSmooth(false);
	pac_texture[13].loadFromFile("../res/sprites/pac_1_k_5.png");
	pac_texture[13].setSmooth(false);
	pac_texture[14].loadFromFile("../res/sprites/pac_1_k_6.png");
	pac_texture[14].setSmooth(false);
	pac_texture[15].loadFromFile("../res/sprites/pac_1_k_7.png");
	pac_texture[15].setSmooth(false);
	pac_texture[16].loadFromFile("../res/sprites/pac_1_k_8.png");
	pac_texture[16].setSmooth(false);
	pac_texture[17].loadFromFile("../res/sprites/pac_1_k_9.png");
	pac_texture[17].setSmooth(false);
	pac_texture[18].loadFromFile("../res/sprites/pac_1_k_10.png");
	pac_texture[18].setSmooth(false);
	pac_texture[19].loadFromFile("../res/sprites/pac_1_k_11.png");
	pac_texture[19].setSmooth(false);
	pac_texture[20].loadFromFile("../res/sprites/pac_1_k_12.png");
	pac_texture[20].setSmooth(false);


	Sprite maze;
	maze.setTexture(maze_texture);
	maze.setPosition(Vector2f(150, 26));

	Sprite game_s;
	game_s.setTexture(game_s_texture);

	Sprite biscuit;
	biscuit.setTexture(biscuit_texture);

	Sprite s_biscuit;
	s_biscuit.setTexture(s_biscuit_texture);

	Sprite pac[21];
	for(int i = 0; i < 21; i++){
		pac[i].setTexture(pac_texture[i]);
	}


	while (window->isOpen()){

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


		memset(buffer, '\0', 2048);
		client_game.recv(0, buffer, 2048);
		msg = string(buffer);

		//Quebra a mensegem para encontrar todos os pontos
		apos = 0;
		pl_info.clear();
		players.clear();
		info.clear();

		while(apos < msg.size()){
			pos = msg.find(';', apos);
			word = msg.substr(apos, pos);
			pl_info.push_back(word);
			apos = pos + 1;
		}

		for(int i = 0; i < pl_info.size(); i++){
			apos = 0;
			while(apos < pl_info.at(i).size()){
				pos = pl_info.at(i).find('|', apos);
				word = pl_info.at(i).substr(apos, pos);
				info.push_back(stoi(word));
				apos = pos + 1;
			}

			Player p(info.at(0), info.at(1));
			p.set_sprites_num(info.at(2));

			players.push_back(p);
		}

        window->clear();

		//Drawn here
		window->draw(game_s);
        window->draw(maze);



		for(int i = 0; i < biscuits.size(); i++){
			biscuit.setPosition(Vector2f(biscuits.at(i).second + 150, biscuits.at(i).first + 26));
			window->draw(biscuit);
		}

		for(int i = 0; i < s_biscuits.size(); i++){
			s_biscuit.setPosition(Vector2f(s_biscuits.at(i).second + 150, s_biscuits.at(i).first + 26));
			window->draw(s_biscuit);
		}

		for(int i = 0; i < players.size(); i++){
			pac[players.at(i).get_sprites_num()].setPosition(players.at(i).get_j() + 150, players.at(i).get_i() + 26);
			window->draw(pac[players.at(i).get_sprites_num()]);
		}

        window->display();
    }
}

void thread_snd(Socket client_game, bool* has_finish, RenderWindow* window){
	XInitThreads();
	cout << "Thread de envio iniciado com sucesso!" << endl;

	char* buffer = new char[10];
	string msg;

	cout << "Bem vindo, digite sua mensagem e pressione enter para enviar" << endl;
	Event event;
	this_thread::sleep_for(chrono::milliseconds(1000));

	while (true){
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

int main(int argc, char **argv){

	string ip = string(argv[1]);
	int port = atoi(argv[2]);
	bool* has_finish = new bool(false);

	//Cria um atributo
	Socket client_game(ip, port);
	RenderWindow* window = new RenderWindow(VideoMode(400, 300), "Pac-Doni");

	//Conecta ao servidor
	cout << "Iniciando conexão..." << endl;
	if(client_game.connect() == 0){

		cout << "Iniciando thread de recebimento..." << endl;
		thread* recv = new thread(thread_rcv, client_game, has_finish, window);
		cout << "Iniciando thread de envio..." << endl;
		thread* send = new thread(thread_snd, client_game, has_finish, window);

		recv->join();
		send->join();

		client_game.close(0);
	}else{
		cout << "Erro ao estabelecer conexão!" << endl;
	}



	return 0;
}
