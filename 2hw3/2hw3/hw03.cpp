/*
2019/02/20
C++ OOP: homework03
Focus:
    Data Hiding
    Encapsulation
    Delegation
    Operator Overloading
Written by Giana Yang

*/
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Warriors {
	friend ostream& operator<<(ostream& os, const Warriors& warrior) {
		os <<  warrior.name << ", weapon: " <<warrior.weapon.name <<", "<<warrior.getStrength() << endl;
		return os;
	}
public:
	Warriors(const string n, const string wp, int p) : name(n), weapon(wp, p) {}
	const string& getName()const { return name; }
	int getStrength() const { return weapon.strength; }

	void battle(Warriors& player2){
		if (player2.getStrength() == 0 && weapon.strength != 0) { //check if the enemy is dead
			cout << name << " battles " << player2.getName() << endl;
			cout << "He's dead, " << name << endl;
		}
		else if (weapon.strength == 0 && player2.getStrength() != 0) { //check if himself is dead
			cout << name << " battles " << player2.getName() << endl;
			cout << "He's dead, " << player2.getName() << endl;
		}
		else if (player2.getStrength() == 0 && weapon.strength == 0) { //check if both are dead
			cout << name << " battles " << player2.getName() << endl;
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if (weapon.strength > player2.getStrength()) { //if him is stronger than the enemy 
			weapon.strength =weapon.strength - player2.getStrength();
			player2.weapon.strength = 0;
			cout << name << " battles " << player2.getName() << endl;
			cout << name << " defeats " << player2.getName() << endl;

		}
		else if (weapon.strength < player2.weapon.strength) { //if him is weaker than the enemy 
			player2.weapon.strength = player2.weapon.strength - weapon.strength;
			weapon.strength = 0;
			cout << name << " battles " << player2.getName() << endl;
			cout << player2.getName() << " defeats " << name << endl;
		}
		else {													//if they are the same strength
			cout << name << " battles " << player2.getName() << endl;
			cout << "Mutual Annihilation: " << name << " and " << player2.getName() << " die at each other's hands" << endl;
			player2.weapon.strength = 0;
			weapon.strength = 0;
		}


	}

private:
	class Weapons {
	public:
		Weapons(const string wp, int p) :name(wp), strength(p) {}
		string name;
		int strength;
	};
	string name;
	Weapons weapon;

};




void openFile(ifstream& ifs)		//openFile 
{
	string filename;
	cout << "filename:";
	cin >> filename;
	ifs.open(filename);
	while (!ifs) {
		cout << "failed to open" << endl;
		cout << "filename:";
		cin >> filename;
		ifs.clear();
		ifs.open(filename);
	}
}
int findWarrior(const string& player, const vector<Warriors>& army) {  //give the warrior's name
	
	for (size_t i = 0; i < army.size(); ++i) {
		if (player == army[i].getName()) {
			return i;							//return the index of the warrior in the vector
		}
	}
	return army.size();
}

void status(const vector<Warriors>& army) {				//call the output operator
	cout << "There are: " << army.size() << " warriors " << endl;
	for (size_t i = 0; i < army.size(); ++i) {
		cout << "Warrior: " << army[i]<< endl;
	}
}

void call_function(ifstream& file, vector<Warriors>& army) {
	string call;
	while (file >> call) {					      //call the functions
		if (call == "Warrior") {
			string name;
			string wp;
			int strength;
			if (file >> name >> wp >> strength) {
				Warriors someone(name, wp, strength);
				army.push_back(someone);
			}
		}
		else if (call == "Status") {
			status(army);
		}
		else if (call == "Battle") {
			string player1, player2;
			size_t pos1, pos2;
			if (file >> player1 >> player2) {
				pos1 = findWarrior(player1, army);
				pos2 = findWarrior(player2, army);
				if (pos1 < army.size() && pos2 < army.size()) {
					army[pos1].battle(army[pos2]);
				}
			}
			else {
				cerr << "Can't not read in warrior" << endl;
			}
		}
	}
}

int main() {
	ifstream file;
	vector <Warriors> army;
	file.open("warriors.txt");
	if (!file) {
		cerr << "Could not open file" << endl;
	}
	call_function(file, army);
	
	file.close();
}