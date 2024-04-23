#include "HumanPlayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(char m) : Player(m) {}

void HumanPlayer::makeMove(Board& board) {
	int row, col;
	while (true) {
		cout << "Enter row and column (0-2): ";
		cin >> row >> col;
		if (row >= 0 && row < 3 && col >= 0 && col < 3 && board.isCellEmpty(row, col)) {
			board.placeMark(row, col, getMark());
			break;
		} else {
			cout << "Invalid move. Try again." << endl;
		}
	}
}