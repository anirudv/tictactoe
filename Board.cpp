#include "Board.h"
#include <iostream>

using namespace std;

Board::Board() {
	resetBoard();
}

void Board::resetBoard() { //this clears the board
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					board[i][j] = '-';
				}
			}
		}

bool Board::isCellEmpty(int row, int col) { //this checks if 
	return board[row][col] == '-';
}

bool Board::placeMark(int row, int col, char mark) {
	if (isCellEmpty(row, col)) {
		board[row][col] = mark;
		return true;
	}
	return false; 
}

bool Board::isBoardFull() {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '-') {
				return false;
			}
		}
	}
	return true;
}

bool Board::checkWin(char mark) {
	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) {
			return true;
		}
		if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark) {
			return true;
		}
	}
	if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) {
		return true;
	}
	if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) {
		return true;
	}
	return false;
}

void Board::display() {
	cout << "  0 1 2\n";
	for (int i = 0; i < 3; ++i) {
		cout << i << " ";
		for (int j = 0; j < 3; ++j) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

			
			
  

