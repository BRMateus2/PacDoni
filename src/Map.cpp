#include "Map.hpp"

Map::Map(int width, int height){
	//Aloca o mapa na mémória
	game_map = new char*[height];
	for(int i = 0; i < height; i++){
		game_map[i] = new char[width];
	}

	//Aloca os recursos restantes
	this->width = new int(width);
	this->height = new int(height);
	this->biscuits = new map<pair<int,int>, char>;
	this->s_biscuits = new map<pair<int,int>, char>;
	this->initial_player_pos = new vector<pair<int,int>>;
	this->initial_ghost_pos = new vector<pair<int,int>>;
}

Map::Map(int width, int height, string map_name){
	//Aloca o mapa na mémória
	game_map = new char*[height];
	for(int i = 0; i < height; i++){
		game_map[i] = new char[width];
	}

	//Aloca os recursos restantes
	this->width = new int(width);
	this->height = new int(height);
	this->biscuits = new map<pair<int,int>, char>;
	this->s_biscuits = new map<pair<int,int>, char>;
	this->initial_player_pos = new vector<pair<int,int>>;
	this->initial_ghost_pos = new vector<pair<int,int>>;

	ifstream loader(map_name.c_str());

	for(int i = 0; i < height; i++ ){
		for(int j = 0; j < width; j++){
			loader >> game_map[i][j];
			if(game_map[i][j] == '5'){
				pair<int, int> b_pos(i,j);
				biscuits->insert(pair<pair<int, int>, char>(b_pos, 'b'));
			}else
			if(game_map[i][j] == '6'){
				pair<int, int> b_pos(i,j);
				s_biscuits->insert(pair<pair<int, int>, char>(b_pos, 's'));
			}else
			if(game_map[i][j] == '3'){
				pair<int, int> b_pos(i,j);
				initial_player_pos->push_back(b_pos);
			}else
			if(game_map[i][j] == '4'){
				pair<int, int> b_pos(i,j);
				initial_ghost_pos->push_back(b_pos);
			}
		}
	}
}

Map::Map(const Map& g_map){
	this->width = new int(*(g_map.width));
	this->height = new int(*(g_map.height));

	this->biscuits = new map<pair<int,int>, char>(*(g_map.biscuits));
	this->s_biscuits = new map<pair<int,int>, char>(*(g_map.s_biscuits));

	this->initial_player_pos = new vector<pair<int,int>>(*(g_map.initial_player_pos));
	this->initial_ghost_pos = new vector<pair<int,int>>(*(g_map.initial_ghost_pos));

	game_map = new char*[*height];
	for(int i = 0; i < *height; i++){
		game_map[i] = new char[*width];
	}

	for(int i = 0; i < *height; i++ ){
		for(int j = 0; j < *width; j++){
			game_map[i][j] = g_map.game_map[i][j];
		}
	}
}

Map::~Map(){
	for(int i = 0; i < *height; i++){
		delete[] game_map[i];
	}

	delete[] game_map;
	delete width;
	delete height;
	delete biscuits;
	delete s_biscuits;
	delete initial_player_pos;
	delete initial_ghost_pos;
}

bool Map::load(string map_name){
	biscuits->clear();
	s_biscuits->clear();
	initial_player_pos->clear();
	initial_ghost_pos->clear();

	ifstream loader(map_name.c_str());

	for(int i = 0; i < *height; i++ ){
		for(int j = 0; j < *width; j++){
			loader >> game_map[i][j];
			if(game_map[i][j] == '5'){
				pair<int, int> b_pos(i,j);
				biscuits->insert(pair<pair<int, int>, char>(b_pos, 'b'));

			}else
			if(game_map[i][j] == '6'){
				pair<int, int> b_pos(i,j);
				s_biscuits->insert(pair<pair<int, int>, char>(b_pos, 's'));
			}else
			if(game_map[i][j] == '3'){
				pair<int, int> b_pos(i,j);
				initial_player_pos->push_back(b_pos);
			}else
			if(game_map[i][j] == '4'){
				pair<int, int> b_pos(i,j);
				initial_ghost_pos->push_back(b_pos);
			}
		}
	}
}

char** Map::get_game_map(){
	return game_map;
}

char Map::get_map_at(int i, int j){
	return game_map[i][j];
}

void Map::set_map_at(int i, int j, char value){
	game_map[i][j] = value;
}

int Map::get_remaining_dots(){
	return (biscuits->size() + s_biscuits->size());
}

int Map::get_width(){
	return *width;
}

int Map::get_height(){
	return *height;
}

map<pair<int,int>, char>* Map::get_biscuits(){
	return biscuits;
}

map<pair<int,int>, char>* Map::get_s_biscuits(){
	return s_biscuits;
}

vector<pair<int,int>>* Map::get_initial_player_pos(){
	return initial_player_pos;
}

vector<pair<int,int>>* Map::get_initial_ghost_pos(){
	return initial_ghost_pos;
}
