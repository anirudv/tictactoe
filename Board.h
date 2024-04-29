#pragma once

class Board {
	private:
		char board[3][3];

	public:
		Board();
		void resetBoard();
		bool isCellEmpty(int row, int col) const;
		bool placeMark(int row, int col, char mark);
		bool isBoardFull() const; 
		bool checkWin(char mark) const;
		void display() const;

		char getMarkAt(int row, int col) const;
    	void setMarkAt(int row, int col, char mark);


};