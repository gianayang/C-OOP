#include "noble.h"
#include "protector.h"
using namespace std;

namespace WarriorCraft {

	Noble::Noble(const string& name) :name(name) {}
	const string& Noble::getName()const { return name; }
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
			this->fight();
			enemy.fight();
			if (ourStrength > enemyStrength) {
				double ratio = 1 - (enemyStrength / ourStrength);
				this->changeStrength(ratio);
				enemy.changeStrength(0.0);
				enemy.dead = true;
				cout << name << " defeats " << enemy.name << endl;
			}
			else if (ourStrength == enemyStrength) {//both dead
				enemy.changeStrength(0.0);
				enemy.dead = true;
				this->changeStrength(0.0);
				dead = true;
				cout << "Mutual Annihalation : " << name << " and " << enemy.name << " die at each other's hands" << endl;
			}
			else {  //enemy wins
				double ratio = 1 - (ourStrength / enemyStrength);
				this->changeStrength(0.0);
				enemy.changeStrength(ratio);
				dead = true;
				cout << enemy.name << " defeats " << name << endl;
			}
		}
	}
	void Lord::fight()const{
		for (Protector* warrior : army) {
			warrior->fight();
		}
	}

	void PersonWithStrengthToFight::fight() const {
		cout << "UGH!!!!!!"<<endl;
	}
	void Lord::changeStrength(double ratio) { 
		if (ratio == 0.0) {
			for (Protector* warrior : army) {
				warrior->changeStrength(0.0); 
			}
		}
		else {
			for (Protector* warrior : army) {
				warrior->changeStrength(ratio);
			}
		}
	}
	bool Noble::getStatus()const { return dead; }
	Lord::Lord(const string& name) :Noble(name) {}
	void Lord::fire(Protector& warrior) {				// a Noble tries to fire a warrior
		if (!getStatus()) {
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
						Protector* temp = army[warriorPos];
						army[warriorPos] = army[warriorPos + 1];
						army[warriorPos + 1] = temp;
					}
				}
				cout << army[army.size() - 1]->getName() << ", you're fired!" << " --" << getName() << endl;
				army.pop_back();
			}
			else {
				cerr << "There is no such warrior hired" << endl;
			}

		}
		else {
			cerr << getName() << "can't fire because he's dead!" << endl;
		}
	}

	void PersonWithStrengthToFight::changeStrength(double ratio) {
		if (ratio == 0.0) {
			strength = 0.0;
		}
		else {
			strength = strength * ratio;
		}
	}
	double Lord::calculateStrength()const {			//measuring army strength for the battle
		double total = 0.0;
		for (const Protector* warrior : army) {
			total += warrior->getStrength();
		}
		return total;
	}
	
	bool Lord::hires(Protector& protector) {			//a Noble tries to hire a warrior
		if (!getStatus()) {
			if (!protector.getHired()) {
				army.push_back(&protector);
				protector.hires(this);
				return true;
			}
		}
		return false;
	}

	PersonWithStrengthToFight::PersonWithStrengthToFight(std::string name, int strength) : Noble(name), strength(strength) {}
	double PersonWithStrengthToFight::calculateStrength()const {return strength; }


	
}