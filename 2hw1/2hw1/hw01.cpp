/*
Spring 2019
hw01
Caesar Cypher
focus:

	vectors
	strings
	functions
	Standard I/O
	Clean code!

Written by Giana Yang
*/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

char undecryptedCha(char origchar,int step) {
	char newchar;
	newchar = origchar - step;
	if (newchar < 'a' ) {
		newchar='z'+1-('a'%newchar); // if it goes below the char value of 'a'
	}
	return newchar;
}

void modify(vector<string>& file, int step) {			
	for (size_t i = 0; i < file.size(); i++) {
		for (size_t j = 0; j < file[i].size(); j++) {
			if ('a' <= file[i][j]&& file[i][j] <= 'z') {		// only lowercase to undecrypt
				char newChar = undecryptedCha(file[i][j], step);  
				file[i][j] = newChar;		//modify the string
			}
		}
	}
	vector<string> fixedOrder;
	int size = file.size() - 1;
	for (size_t i = 0; i < file.size(); i++) { //switch lines
		fixedOrder.push_back(file[size-i]);
	}
	/*size_t j=0;
	for(size_t i=m.size();j<m.size();i--,j++){}
	file = fixedOrder;
	*/
}

int openFile(ifstream& ifs, vector<string>& file) {
	int step;
	string line;
	if (ifs >> step) {  //get the number
		while (getline(ifs, line)) {
			file.push_back(line);
		}
	}
	return step;
}

int main() {
	const char* filename = "encrypted.txt";
	ifstream ifs;
	ifs.open(filename);
	vector<string> file;
	int step=openFile(ifs,file);
	modify(file,step);
	for (size_t i = 0; i < file.size(); i++) {
		cout << file[i] << endl;
	}
	ifs.close();
}
