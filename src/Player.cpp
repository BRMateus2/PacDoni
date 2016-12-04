#include "Player.hpp"

Player::Player(int i, int j, int id){
	this->i = new int(i);
	this->j = new int(j);
	this->id = new int(id);
	this->super_force = new int(0);
	this->eaten_biscuits = new int(0);
	this->direction = new int(3);
	this->desired_direction = new int(3);
	this->sprite_num = new int(0);
	this->lifes = new int(4);
	this->item = new int(0);
	this->sound_num = new int(0);
	this->wait_time = new int(0);
}

Player::Player(const Player& p){
	this->i = new int(*(p.i));
	this->j = new int(*(p.j));
	this->id = new int(*(p.id));
	this->super_force = new int(*(p.super_force));
	this->eaten_biscuits = new int(*(p.eaten_biscuits));
	this->direction = new int(*(p.direction));
	this->desired_direction = new int(*(p.desired_direction));
	this->sprite_num = new int(*(p.sprite_num));
	this->lifes = new int(*(p.lifes));
	this->item = new int(*(p.item));
	this->sound_num = new int(*(p.sound_num));
	this->wait_time = new int(*(p.wait_time));
}

Player::~Player(){
	delete i;
	delete j;
	delete id;
	delete super_force;
	delete eaten_biscuits;
	delete direction;
	delete desired_direction;
	delete sprite_num;
	delete lifes;
	delete item;
	delete sound_num;
	delete wait_time;
}


void Player::set_i(int i){
	*(this->i) = i;
}

int Player::get_i(){
	return *(this->i);
}

void Player::set_j(int j){
	*(this->j) = j;
}

int Player::get_j(){
	return *(this->j);
}

void Player::set_id(int id){
	*(this->id) = id;
}

int Player::get_id(){
	return *(this->id);
}

int Player::get_super_force(){
	return *super_force;
}

void Player::decrease_super_force(){
	if(*(super_force) > 0){
		*(super_force) -= 1;
	}
}

void Player::fill_super_force(){
	*super_force = 1000;
}


void Player::set_eaten_biscuits(int eaten_biscuits){
	*(this->eaten_biscuits) = eaten_biscuits;
}

int Player::get_eaten_biscuits(){
	return *(this->eaten_biscuits);
}

void Player::set_direction(int direction){
	*(this->direction) = direction;
}

int Player::get_direction(){
	return *(this->direction);
}

void Player::set_desired_direction(int desired_direction){
	*(this->desired_direction) = desired_direction;
}

int Player::get_desired_direction(){
	return *(this->desired_direction);
}

void Player::set_sprites_num(int sprite_num){
	*(this->sprite_num) = sprite_num;
}

int Player::get_sprites_num(){
	return *(this->sprite_num);
}

void Player::set_lifes(int lifes){
	*(this->lifes) = lifes;
}

int Player::get_lifes(){
	return *(this->lifes);
}

void Player::set_item(int item){
	*(this->item) = item;
}

int Player::get_item(){
	return *(this->item);
}

void Player::set_sound_num(int sound_num){
	*(this->sound_num) = sound_num;
}

int Player::get_sound_num(){
	return *(this->sound_num);
}

void Player::decrease_wait_time(){
	if(*wait_time > 0){
		*(wait_time) -= 1;
	}
}

void Player::fill_wait_time(){
	*(this->wait_time) = 100;
}


int Player::get_time_wait(){
	return *(this->wait_time);
}
