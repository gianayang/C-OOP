/*
2019/03/07
Homework 05
Focus:

	Dynamic memory 

Written by Giana Yang
*/
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Warrior {
	friend ostream& operator << (ostream& os, const Warrior& warrior) {   //output operator to display the status
		os << "	" << warrior.getName() << ": " << warrior.getStrength() << endl;
		return os;
	}
public:
	Warrior(const string& name, int str) :name(name), strength(str) {}
	double getStrength()const { return strength; }  //get the strength for status display
	bool getHired()const { return hired; } //get access to hire status for "unemployeed"
	const string& getName()const { return name; } //get access to name for "unemployeed"status
	bool hire() {							//to see if the warrior is already hired,change the state of hiring
		if (hired == false) {
			hired = true;
			return false;
		}
		else {
			cerr << name << " is already hired!" << endl;
			return true;
		}
	}
	bool fire() {
		if (hired == true) { //if the warrior is hired, the noble can fire him.
			hired = false;
			return true;
		}
		else {
			cerr << name << " is already fired!" << endl;
			return false;
		}
	}

	void changeStrength(double harm) {				//take the percentage of harm and change the strength to after battle
		strength = strength * harm;
	}
	void changeStrengthtoZero() {  //dead 
		strength = 0;
	}
private:
	double strength;
	string name;
	bool hired = false;
};


class Noble {
	friend ostream& operator << (ostream& os,const Noble& noble) { //output operator for noble
		os << noble.getName() << " has an army of " << noble.army.size() << endl;
		if (noble.army.size() != 0) {
			for (const Warrior* warrior : noble.army) {
				os << *warrior;
			}
		}
		else {
			os << endl;
		}
		return os;
	}

public:
	Noble(const string& name) :name(name) {} 
	const string& getName() const { return name; } //get access to name from outside of the class
	void battle(Noble& enemy) {				//battle
		cout << name << " battles " << enemy.name << endl;
		if (enemy.dead && !this->dead) { //check if the enemy is dead
			cout << "He's dead, " << name << endl;
		}
		else if (this->dead && !enemy.dead) { //check if himself is dead
			cout << "He's dead, " << enemy.name << endl;
		}
		else if (this->dead == true && enemy.dead == true) { //check if both are dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else {
			double ourStrength = this->calculateStrength();
			double enemyStrength = enemy.calculateStrength();
			if (ourStrength > enemyStrength) {
				double ratio = 1 - (enemyStrength / ourStrength);
				for (Warrior* warrior : army) {
					warrior->changeStrength(ratio);
				}
				for (Warrior* warrior : enemy.army) {
					warrior->changeStrengthtoZero();
				}
				enemy.dead = true;
				cout << name << " defeats " << enemy.name << endl;
			}
			else if (ourStrength == enemyStrength) {//both dead
				for (Warrior* warrior : enemy.army) {
					warrior->changeStrengthtoZero();
				}
				enemy.dead = true;
				for (Warrior* warrior : army) {
					warrior->changeStrengthtoZero();
				}
				dead = true;
				cout << "Mutual Annihalation : " << name << " and " << enemy.name << " die at each other's hands" << endl;
			}
			else {  //enemy wins
				double ratio = 1 - (ourStrength / enemyStrength);
				for (Warrior* warrior : army) {
					warrior->changeStrengthtoZero();
				}
				for (Warrior* warrior : enemy.army) {
					warrior->changeStrength(ratio);
				}
				dead = true;
				cout << enemy.name << " defeats " << name << endl;
			}
		}
	}

	bool hire(Warrior& warrior) {			//a Noble tries to hire a warrior
		if (!dead) {
			if (warrior.hire() == false) {
				army.push_back(&warrior);
				return true;
			}
		}
		return false;
	}

	void fire(Warrior& warrior) {				// a Noble tries to fire a warrior
		if (!dead) {
			warrior.fire();
			int warriorPos = -1;
			for (size_t i = 0; i < army.size(); ++i) {
				if (army[i] == &warrior) {
					warriorPos = i;
					break;
				}
			}
			if (warriorPos != -1) {
				if (warriorPos != army.size() - 1) { //delete the warrior out of the army after firing him
					for (size_t i = warriorPos; i < army.size() - 1; ++i) {
						Warrior* temp = army[warriorPos];
						army[warriorPos] = army[warriorPos + 1];
						army[warriorPos + 1] = temp;
					}
				}
				cout << army[army.size() - 1]->getName() << ", you're fired!" << " --" << name << endl;
				army.pop_back();
			}
			else {
				cerr << "There is no such warrior hired" << endl;
			}
			
		}
		else {
			cerr << name << "can't fire because he's dead!" << endl;
		}
	}

private:
	string name;
	bool dead = false;
	vector<Warrior*> army;

	double calculateStrength()const {			//measuring army strength for the battle
		double total = 0;
		for (const Warrior* warrior : army) {
			total += warrior->getStrength();
		}
		return total;
	}
};

ifstream& openFile(ifstream& ifs)
{
	ifs.open("nobleWarriors.txt");
	while (!ifs) {
		cerr << "failed to open" << endl;
		exit(1);
	}
	return ifs;
}
size_t nobleExist(const string& name, const vector<Noble*>& noble)  { //check if noble already exists, also use to find noble in the vector
	for (size_t i = 0; i < noble.size(); ++i) {
		if (name == noble[i]->getName()) {
			return i; //return the index, where is noble in a vector
		}
	}
	return noble.size();
}

size_t warriorExist(const string& name, const vector<Warrior*>& warrior){ //check if warrior already exists
	for (size_t i = 0; i < warrior.size(); ++i) {
		if (name == warrior[i]->getName()) {
			return i;//find the index of the warrior in a vector
		}
	}
	return warrior.size();
}

void clear(vector <Warrior*>& army, vector <Noble*>& nobles) { // clear heap
	for (size_t i = 0; i < nobles.size(); ++i) {
		delete nobles[i];
	}
	nobles.clear();

	for (size_t j = 0; j < army.size(); ++j) {
		delete army[j];
	}
	army.clear();

}

void functionApply(ifstream& ifs, vector <Warrior*>& warrior, vector <Noble*>& noble) { //read from file 
	string calling;
	while (ifs >> calling) {
		if (calling == "Noble") {
			string name;
			if (ifs >> name) {
				if (nobleExist(name, noble)==noble.size()) {//noble is not in the vector yet
					Noble* newNoble = new Noble(name);
					noble.push_back(newNoble);
				}
				else {
					cerr << "Noble does exist" << endl;
				}
			}
		}
		else if (calling == "Warrior") {
			string name;
			int strength;
			if (ifs >> name>>strength) {
				if (warriorExist(name,warrior)==warrior.size()) {//warrior is not in the vector yet
					Warrior* newWarrior = new Warrior(name,strength);
					warrior.push_back(newWarrior);
				}
				else {
					cerr << "Warrior does exist" << endl;
				}
			}
		}
		else if (calling == "Hire") {
			string hirer, employee;
			int pos1, pos2;
			if (ifs >> hirer >> employee) {
				pos1 = nobleExist(hirer, noble);
				pos2 = warriorExist(employee, warrior);
				if (pos1 != noble.size() & pos2 != warrior.size()) {
					noble[pos1]->hire(*warrior[pos2]);
				}
				
			}
		}
		else if (calling == "Fire") {
			string hirer, employee;
			int pos1, pos2;
			if (ifs >> hirer >> employee) {
				pos1 = nobleExist(hirer, noble);
				pos2 = warriorExist(employee, warrior);
				if (pos1 != noble.size() & pos2 != warrior.size()) {
					noble[pos1]->fire(*warrior[pos2]);
				}
			}
		}
		else if (calling == "Status") {
			cout << "Status" << endl;
			cout << "=======" << endl;
			if (noble.size() == 0) {
				cout << "NONE" << endl;
			}
			else{
				for (const Noble* nobles : noble) {
					cout << *nobles;
				}
			}
			cout << "Unemployed Warriors:" << endl;
			bool unemployed = false; // check if there are any unemployed in the heap
			for (size_t j = 0; j < warrior.size(); ++j) {
				if (warrior[j]->getHired() == false) {
					unemployed = true;
					cout << *warrior[j] << endl;
				}
			}
			if (unemployed == false) {
				cout << "NONE" << endl;
			}
		}
		else if (calling=="Battle") {
			string noble1, noble2;
			int pos1, pos2;
			if (ifs >> noble1 >> noble2) {
				pos1 = nobleExist(noble1, noble);
				pos2 = nobleExist(noble2,noble);
				if (pos1 != noble.size() & pos2 != warrior.size()) {
					noble[pos1]->battle(*noble[pos2]);
				}
			}
		}
		else {
			clear(warrior,noble);
		}
	}
	

}
int main() {
	vector <Warrior*> warrior;
	vector <Noble*> noble;
	ifstream file;
	openFile(file);
	functionApply(file, warrior, noble);
	file.close();//close the file
}