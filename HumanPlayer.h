#pragma once
#include "Player.h"

class HumanPlayer : public Player {
	public:
		HumanPlayer(char m);
		virtual void makeMove(Board& board) override;

};