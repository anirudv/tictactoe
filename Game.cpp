#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : playerX('X'), playerO('O') {}

void start() {
	board.resetBoard();
	currentPlayer = &playerX;
}

void play () {
	int row;
	int col;
	while(true):

		cout << "current board: \n";
		board.display();

		cout << currentPlayer->getMark() << " turn. Enter a row and column number between 0 and 2 separated by a space. Ex: 0 2 \n";
		cin >> row >> col;

		if (row < 0 || row > 2 || col < 0 || col > 2) {
			cout << "Invalid\n" << endl;
			continue;
		}

		if (board.placeMark(row, col, currentPlayer->getMark())) {
			if (board.checkWin(currentPlayer->getMark())) {
				cout << currentPlayer->getMark() << " wins!\n" << endl;
				break;
			}
			
			if (board.isBoardFull())
			{
				cout << "draw\n" << endl;
				break;
			}

			if (currentPlayer == &playerX) {
				currentPlayer = &playerO;
			}
			else {
				currentPlayer = &playerX;
			}
		}
		else {
			cout << "cell occupied. pick another one please \n"
		}
}

