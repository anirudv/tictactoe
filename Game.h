#pragma once
#include "Board.h"
#include "Player.h"

class Game {
	private: 
		Board board;
		Player playerX;
		Player playerO;
		Player* currentPlayer;

	public:
		Game();
		void start();
		void play();
};