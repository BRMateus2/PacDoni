#pragma once

class Player{
private:
	int* i;
	int* j;
	int* id;
	int* super_force;
	int* eaten_biscuits;
	int* direction;
	int* desired_direction;
	int* sprite_num;
	int* lifes;
	int* item;
	int* sound_num;
	int* wait_time;

public:
	Player(int i, int j, int id);
	Player(const Player& p);
	~Player();

	void set_i(int i);
	int get_i();

	void set_j(int j);
	int get_j();

	void set_id(int id);
	int get_id();

	int get_super_force();
	void set_super_force(int super_force);
	void decrease_super_force();
	void fill_super_force();

	void set_eaten_biscuits(int eaten_biscuits);
	int get_eaten_biscuits();

	void set_direction(int direction);
	int get_direction();

	void set_desired_direction(int desired_direction);
	int get_desired_direction();

	void set_sprites_num(int sprite_num);
	int get_sprites_num();

	void set_lifes(int lifes);
	int get_lifes();

	void set_item(int item);
	int get_item();

	void set_sound_num(int sound_num);
	int get_sound_num();

	void decrease_wait_time();
	void fill_wait_time();
	int get_time_wait();
};
