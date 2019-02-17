/*
02/15/2019 Lab 03: Minesweeper
Focus:
Basics of OOP: 
	Encapuslation and Data Hiding
Code Written by Giana Yang
*/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Tile {
	bool bomb = false;
	bool revealed = false;
	int neighbor = 0;
	bool done = false;
};

struct Cord {  //to-do list
	int r;
	int c;
};

class Minesweeper {
public:
	Minesweeper():board(), row(10), col(10) {
		srand(time(NULL));
		for (int i = 0; i < (row + 2); ++i) {
			vector<Tile> blank;
			board.push_back(blank);
			for (int j = 0; j < (col + 2); ++j) {
				Tile miniTile;
				if (i == 0 || j == 0) {
					miniTile.done = true;
				}
				else if (i == row + 1 || j == col + 1) {
					miniTile.done = true;
				}
				else if ((rand() % 100) < BOMB_PROBABILITY) {
					miniTile.bomb = true;
				}
				board[i].push_back(miniTile);
			}
		}
		set_neighbor();
	};
			
	void set_neighbor(){
		for (int i = 1; i < row + 1; ++i) {
			for (int j = 1; j < col + 1; ++j) {
				if (!board[i][j].bomb) {
					int nei = 0;
					if (board[i - 1][j - 1].bomb == true) {
						nei++;
					}
					if (board[i - 1][j].bomb == true) {
						nei++;
					}
					if (board[i - 1][j + 1].bomb == true) {
						nei++;
					}
					if (board[i][j - 1].bomb == true) {
						nei++;
					}
					if (board[i][j + 1].bomb == true) {
						nei++;
					}
					if (board[i + 1][j - 1].bomb == true) {
						nei++;
					}
					if (board[i + 1][j + 1].bomb == true) {
						nei++;
					}
					if (board[i + 1][j].bomb == true) {
						nei++;
					}
					board[i][j].neighbor = nei;
				}
			}
		}
	}

	 void display(bool reveal)const{
		if (reveal == true) {
			for (size_t i = 1; i < row + 1; ++i) {
				for (size_t j = 1; j < col + 1; ++j) {
					if (board[i][j].bomb) {
						cout << '*' << ' ';
					}
					/*else if (board[i][j].flaged) {
						cout << 'F' << ' ';
					}*/
					else {
						cout <<' '<< board[i][j].neighbor << ' ';
					}
				}
				cout << endl;
			}
		}
		else {
			for (size_t i = 1; i < row + 1; ++i) {
				for (size_t j = 1; j < col + 1; ++j) {
					if (board[i][j].revealed == true) {
						cout << ' ' << board[i][j].neighbor << ' ';
					}
					else {
						cout << " - ";
					}
				}
				cout << endl;
			}
		}
		cout << endl;
	};

	bool done() {
		for (int i = 1; i < row + 2; ++i) {
			for (int j = 1; j < col + 2; ++j) {
				if (board[i][j].bomb == false && board[i][j].revealed == false) { //if it's not a bomb and it has not been reveal yet
					return false;
				}
			}
		}
		return true;
	}

	bool validRow(int rowNum) {
		return rowNum < row + 1;  //check if the input number exceed the boar
	}

	bool validCol(int colNum) {//check if the input number exceed the board
		return colNum < col + 1;
	}

	bool isVisible(int rowNum, int colNum) {
		return board[rowNum][colNum].revealed;
	}

	bool play(int rowNum, int colNum) {
		if (board[rowNum][colNum].bomb == true) {
			return false;
		}

		Cord point;
		point.r = rowNum;
		point.c = colNum;
		vector<Cord> toDoList;
		toDoList.push_back(point);
		while (toDoList.size() != 0) {
			Cord pointer = toDoList.back();
			toDoList.pop_back();
			if (board[pointer.r][pointer.c].done) { //check if it need to be added to the to-do-list
				continue;
			}

			board[pointer.r][pointer.c].revealed = true;
			if (board[pointer.r][pointer.c].neighbor == 0) {
				for (size_t i = -1; i < 2; i++) {
					for (size_t j = -1; j < 2; j++) {
						Cord newPoint;
						newPoint.c = pointer.c + j;
						newPoint.r = pointer.r + i;
						toDoList.push_back(newPoint); //add to the to-do-list
					}
				}
			}
		}
		return true;
	}

private:
	vector<vector<Tile>> board;
	int row;
	int col;
	const int BOMB_PROBABILITY = 10;
};


int main() {
	Minesweeper sweeper;
	// Continue until only invisible cells are bombs
	while (!sweeper.done()) {
		sweeper.display(false);// display board without bombs
		int row_sel = -1, col_sel = -1;
		while (row_sel == -1) {
			// Get a valid move
			int r, c;
			cout << "row? ";
			cin >> r;
			if (!sweeper.validRow(r)) {
				cout << "Row out of bounds\n";
				continue;
			}
			cout << "col? ";
			cin >> c;
			if (!sweeper.validCol(c)) {
				cout << "Column out of bounds\n";
				continue;
			}
			if (sweeper.isVisible(r, c)) {
				cout << "Square already visible\n";
				continue;
			}
			row_sel = r;
			col_sel = c;
		}

		// Set selected square to be visible. May effect other cells.
		if (!sweeper.play(row_sel, col_sel)) {
			cout << "Sorry, you died..\n";
			sweeper.display(true); // Final board with bombs shown
			system("pause");
			exit(0);
		}
		
	}
	// Ah! All invisible cells are bombs, so you won!
	cout << "You won!!!!\n";
	sweeper.display(true); // Final board with bombs shown
}