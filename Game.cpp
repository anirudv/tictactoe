#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : playerX('X'), playerO('O') {}

void Game::start() {
	board.resetBoard();
	currentPlayer = &playerX;
}

void Game::play () {
	int row;
	int col;
	while(true) {

		cout << "current board: \n";
		board.display();

		cout << currentPlayer->getMark() << " turn. Enter a row and column number between 0 and 2 separated by a space. \n";
		currentPlayer->makeMove(board);

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
	}

