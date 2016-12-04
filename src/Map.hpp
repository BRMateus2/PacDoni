#pragma once

#include <string>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class Map{
private:
	char** game_map;
	int* width;
	int* height;
	map<pair<int,int>, char>* biscuits;
	map<pair<int,int>, char>* s_biscuits;
	vector<pair<int,int>>* initial_player_pos;

public:
	Map(int width, int height);
	Map(int width, int height, string map_name);
	Map(const Map& g_map);
	~Map();

	bool load(string map_name);
	char** get_game_map();
	char get_map_at(int i, int j);
	void set_map_at(int i, int j, char value);
	int get_remaining_dots();
	int get_width();
	int get_height();
	map<pair<int,int>, char>* get_biscuits();
	map<pair<int,int>, char>* get_s_biscuits();
	vector<pair<int,int>>* get_initial_player_pos();
};
