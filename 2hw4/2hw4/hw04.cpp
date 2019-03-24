/*
2019/02/24
Homework 04
Focus:
	
    Classes
    Association
*/
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Warrior {
public:
	Warrior(const string& name, int str):name(name),strength(str){}
	double getStrength()const { return strength; }
	string getName()const { return name; }
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

	void changeStrength(double harm) {				//change strength after the battle
		strength = strength * harm;
	}
	void changeStrengthtoZero() {  //dead 
		strength = 0;
	}
private:
	double strength;
	string name;
	bool hired=false;
};
class Noble {
public:
	Noble(const string& name):name(name){}
	void battle(Noble& enemy){				//battle
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
			else if (ourStrength == enemyStrength) {
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
			if (warrior.hire()==false) {
				army.push_back(&warrior);
				return true;
			}
		}
		return false;
	}
	 
	void fire(Warrior& warrior) {				// a Noble tries to fire a warrior
		if (!dead) {
			int warriorPos = 0;
			for (size_t i = 0; i < army.size(); ++i) {
				if (army[i] == &warrior) {
					warriorPos = i;
					break;
				}
			}
			if (warriorPos != army.size() - 1) {
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
			cerr << name << "can't fire because he's dead!" << endl;
		}
	}
	
	double calculateStrength()const {			//measuring army strength for the battle
		double total = 0;
		for (const Warrior* warrior : army) {
			total += warrior->getStrength();
		}
		return total;
	}

	void display()const {
		cout << name << " has an army of " << army.size() << endl;
		if (army.size() != 0) {
			for (const Warrior* warrior : army) {
				cout << "	" << warrior->getName() << ": " << warrior->getStrength() << endl;
			}
		}
		else {
			cout << endl;
		}
	}
private:
	string name;
	bool dead = false;
	vector<Warrior*> army;
};



int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);


	// NEW OUTPUT CODE
	cout << "==========\n"
		<< "Status after all battles, etc.\n";
	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

}