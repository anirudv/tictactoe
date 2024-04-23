#pragma once
#include "Board.h"
#include "HumanPlayer.h"

class Game {
	private: 
		Board board;
		HumanPlayer playerX;
		HumanPlayer playerO;
		Player* currentPlayer;

	public:
		Game();
		void start();
		void play();
};