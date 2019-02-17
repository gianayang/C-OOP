/*
recitation01
C++ Basics: Implement Conway's Game of Life
focus:
strings,vectors,I/O
Code Written by Giana Yang, 2019/02/01

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


int main() {
	ifstream ifs("life.txt");
	if (!ifs) {
		cerr << "Could not open the file.\n";
		exit(1);
	}
	string line;
	vector<string>system;
	vector<string>newSystem;
	int neighbor=0;
	while (getline(ifs, line)) {
		system.push_back(line);
	}

	cout << "Initial world" << endl;
	for (size_t i = 0; i < system.size(); ++i) {
		cout << system[i] << endl;
	}
	cout << "============================" << endl;

	string border(system[0].size()+2, '-');
	newSystem.push_back(border);
	for (string line : system) {
		newSystem.push_back('-' + line + '-');
	}
	newSystem.push_back(border);
	system = newSystem;

	for (size_t k = 1; k < 11; ++k) {
		for (size_t i = 1; i < system.size()-1; ++i) {
			for (size_t j = 1; j < system[0].size()-1; ++j) {
				neighbor = 0;
				if (system[i - 1][j - 1] == '*') {
					neighbor++;
				}
				if (system[i - 1][j] == '*') {
					neighbor++;
				}
				if (system[i - 1][j + 1] == '*') {
					neighbor++;
				}
				if (system[i][j - 1] == '*') {
					neighbor++;
				}
				if (system[i][j + 1] == '*') {
					neighbor++;
				}
				if (system[i + 1][j - 1] == '*') {
					neighbor++;
				}
				if (system[i + 1][j] == '*') {
					neighbor++;
				}
				if (system[i + 1][j + 1] == '*') {
					neighbor++;
				}

				if (system[i][j] == '-' && neighbor == 3) { // become alive
					newSystem[i][j] = '*';
				}
				else if (system[i][j] == '*' && (neighbor == 2 || neighbor == 3)) {//still alive
					newSystem[i][j] = '*';
				}
				else {										//dead or remain dead
					newSystem[i][j] = '-';
				}
			}
			
		}
		system = newSystem;
		cout << "Generation: " << k << endl;
		for (size_t i = 1; i < system.size() - 1; i++) {
			for (size_t j = 1; j < system[0].size() - 1; j++) {
				cout << system[i][j];
			}
			cout << endl;
		}
		cout << "============================" << endl;
	}

	ifs.close();
}