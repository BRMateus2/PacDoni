#pragma once

class Ghost{
private:
	int* i;
	int* j;
	int* ini_i;
	int* ini_j;
	int* direction;
	int* wait_time;
	int* sprite_num;
	bool* scared;
	bool* alive;
	bool* positioning;

public:
	Ghost(int i, int j);
	Ghost(const Ghost& g);
	~Ghost();
	void set_i(int i);
	int get_i();
	void set_j(int j);
	int get_j();
	int get_ini_i();
	int get_ini_j();
	void set_direction(int direction);
	int get_direction();
	void fill_wait_time();
	void reset_wait_time();
	void decrease_wait_time();
	bool is_waiting();
	void set_sprites_num(int sprite_num);
	int get_sprites_num();
	void set_scared(bool scared);
	bool is_scared();
	void set_alive(bool alive);
	bool is_alive();
	void set_positioning(bool positioning);
	bool is_positioning();
};
