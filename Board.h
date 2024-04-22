#pragma once

class Board {
	private:
		char board[3][3];

	public:
		Board();
		void resetBoard();
		bool isCellEmpty(int row, int col);
		bool placeMark(int row, int col, char mark);
		bool isBoardFull();
		bool checkWin(char mark);
		void display();


};