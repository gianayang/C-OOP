#include "noble.h"
#include "warrior.h"
using namespace std;

namespace WarriorCraft {
	Noble::Noble(const string& name) :name(name) {}
	const string& Noble::getName() const { return name; } //get access to name from outside of the class
	void Noble::battle(Noble& enemy) {				//battle
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
				this->changeStrength(ratio);
				enemy.changeStrength(0);
				enemy.dead = true;
				cout << name << " defeats " << enemy.name << endl;
			}
			else if (ourStrength == enemyStrength) {//both dead
				enemy.changeStrength(0);
				enemy.dead = true;
				this->changeStrength(0);
				dead = true;
				cout << "Mutual Annihalation : " << name << " and " << enemy.name << " die at each other's hands" << endl;
			}
			else {  //enemy wins
				double ratio = 1 - (ourStrength / enemyStrength);
				this->changeStrength(0);
				enemy.changeStrength(ratio);
				dead = true;
				cout << enemy.name << " defeats " << name << endl;
			}
		}
	}

	bool Noble::hire(Warrior& warrior) {			//a Noble tries to hire a warrior
		if (!dead) {
			if (!warrior.getHired()) {
				army.push_back(&warrior);
				warrior.hire(this);
				return true;
			}
		}
		return false;
	}
	

	void Noble::fire(Warrior& warrior) {				// a Noble tries to fire a warrior
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

	void Noble::changeStrength(int ratio) { //pass in 0 if the noble is going to die
		if (ratio == 0) {
			for (Warrior* warrior : army) {
				warrior->changeStrengthtoZero();
			}
		}
		else {
			for (Warrior* warrior : army) {
				warrior->changeStrength(ratio);
			}
		}
		
	}

	double Noble::calculateStrength()const {			//measuring army strength for the battle
		double total = 0;
		for (const Warrior* warrior : army) {
			total += warrior->getStrength();
		}
		return total;
	}

	ostream& operator << (ostream& os, const Noble& noble) { //output operator for noble
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
}