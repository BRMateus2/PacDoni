#include "Ghost.hpp"

Ghost::Ghost(int i, int j){
	this->i = new int(i);
	this->j = new int(j);
	this->ini_i = new int(i);
	this->ini_j = new int(j);
	this->direction = new int(1);
	this->wait_time = new int(40);
	this->sprite_num = new int(0);
	this->scared = new bool(false);
	this->alive = new bool(true);
	this->positioning = new bool(false);
}

Ghost::Ghost(const Ghost& g){
	this->i = new int(*(g.i));
	this->j = new int(*(g.j));
	this->ini_i = new int(*(g.ini_i));
	this->ini_j = new int(*(g.ini_j));
	this->direction = new int(*(g.direction));
	this->wait_time = new int(*(g.wait_time));
	this->sprite_num = new int(*(g.sprite_num));
	this->scared = new bool(*(g.scared));
	this->alive = new bool(*(g.alive));
	this->positioning = new bool(*(g.positioning));
}

Ghost::~Ghost(){
	delete i;
	delete j;
	delete ini_i;
	delete ini_j;
	delete direction;
	delete wait_time;
	delete sprite_num;
	delete scared;
	delete alive;
	delete positioning;
}

void Ghost::set_i(int i){
	*(this->i) = i;
}

int Ghost::get_i(){
	return *(this->i);
}

void Ghost::set_j(int j){
	*(this->j) = j;
}

int Ghost::get_j(){
	return *(this->j);
}

int Ghost::get_ini_i(){
	return *(this->ini_i);
}

int Ghost::get_ini_j(){
	return *(this->ini_j);
}

void Ghost::set_direction(int direction){
	*(this->direction) = direction;
}

int Ghost::get_direction(){
	return *(this->direction);
}

void Ghost::fill_wait_time(){
	*(this->wait_time) = 40;
}

void Ghost::reset_wait_time(){
	*(this->wait_time) = 0;
}

void Ghost::decrease_wait_time(){
	if(*wait_time > 0){
		*wait_time--;
	}
}

bool Ghost::is_waiting(){
	if(*wait_time == 0){
		return false;
	}else{
		return true;
	}
}

void Ghost::set_sprites_num(int sprite_num){
	*(this->sprite_num) = sprite_num;
}

int Ghost::get_sprites_num(){
	return *(this->sprite_num);
}
void Ghost::set_scared(bool scared){
	*(this->scared) = scared;
}

bool Ghost::is_scared(){
	return *(this->scared);
}

void Ghost::set_alive(bool alive){
	*(this->alive) = alive;
}

bool Ghost::is_alive(){
	return *(this->alive);
}

void Ghost::set_positioning(bool positioning){
	*(this->positioning) = positioning;
}

bool Ghost::is_positioning(){
	return *(this->positioning);
}
