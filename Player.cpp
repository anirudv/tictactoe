#include "Player.h"
#include <iostream>

Player::Player(char m) : mark(m) {}

char Player::getMark() const{
	return mark;
}