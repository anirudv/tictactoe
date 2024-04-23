#pragma once
#include "Board.h"

class Player {
	private:
		char mark;
	public:
		Player(char m);
		char getMark() const;
		virtual void makeMove(Board& board) = 0;
};