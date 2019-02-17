/*
OOP C++
2019/02/11
homework 02: Model a gmae of medieval times
Focus:
	Functions
	Structs
	Vectors
	I/O
Written by Giana Yang
*/

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

struct Warrior {
	string name;
	int strength;
};


void status(const vector<Warrior>& army) {
	cout << "There are: " << army.size() << " warriors " << endl;
	for (size_t i = 0; i < army.size(); ++i) {
		cout << "Warrior: " << army[i].name << ", strength: " << army[i].strength << endl;
	}
}

void makeWarrior(ifstream& ifs, vector<Warrior>& army) {
	string name;
	int strength;
	Warrior warrior;
	if(ifs >> name >> strength){
		warrior.name = name;
		warrior.strength = strength;
		army.push_back(warrior);
	}
}

int findWarrior(string& player,const vector<Warrior>& army) {  //give the warrior's name
	int pos1 = army.size();
	for (size_t i = 0; i < army.size(); ++i) {
		if (player == army[i].name) {
			pos1 = i;
		}
		else if (pos1 != army.size()) {			 //end the loop earlier if found the warrior in the vector
			break;
		}
	}
	return pos1;				//return the index of the warrior in the vector
}

void battle(ifstream& ifs, vector<Warrior>& army) {
	string player1, player2;
	int pos1 = army.size();
	int pos2 = army.size();
	if (ifs >> player1 >> player2) { 
		pos1 = findWarrior(player1,army);	//call the find the warrior in the vector function
		pos2 = findWarrior(player2, army);
	}

	if (army[pos2].strength == 0 && army[pos1].strength != 0) { //check if the enemy is dead
		cout << player1 << " battles " << player2 << endl;
		cout << "He's dead, " << player1 << endl;
	}
	else if (army[pos1].strength == 0 && army[pos2].strength != 0) { //check if himself is dead
		cout << player1 << " battles " << player2 << endl;
		cout << "He's dead, " << player2 << endl;
	}
	else if(army[pos2].strength == 0 && army[pos1].strength == 0) { //check if both are dead
		cout << player1 << " battles " << player2 << endl;
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
	else if (army[pos1].strength > army[pos2].strength) { //if him is stronger than the enemy 
		army[pos1].strength = army[pos1].strength - army[pos2].strength;
		army[pos2].strength = 0;
		cout << player1 << " battles " << player2 << endl;
		cout << player1 << " defeats " << player2 << endl;

	}
	else if (army[pos1].strength < army[pos2].strength) { //if him is weaker than the enemy 
		army[pos2].strength = army[pos2].strength - army[pos1].strength;
		army[pos1].strength = 0;
		cout << player1 << " battles " << player2 << endl;
		cout << player2 << " defeats " << player1 << endl;
	}
	else{													//if they are the same strength
		cout << player1 << " battles " << player2 << endl; 
		cout << "Mutual Annihilation: " << player1 << " and " << player2 << " die at each other's hands" << endl;
		army[pos2].strength = 0;
		army[pos1].strength = 0;
	}
	
}

int main() {
	ifstream file;
	file.open("warriors.txt");
	if (!file) {
		cerr << "Could not open file" << endl;
	}
	vector<Warrior> army;
	string call;
	while (file >> call) {					      //call the functions
		if (call == "Warrior") {
			makeWarrior(file, army);			 //call the function to make a instance of the warrior
		}
		else if (call == "Status") {			//output the status of all the warriors
			status(army);
		}
		else {
			battle(file, army);				   //call the battle function
		}
	}
	file.close();
}