#include "Player.h"
#include <iostream>

Player::Player(char m) : mark(m) {}

Player::~Player() {}


char Player::getMark() const{
	return mark;
}
