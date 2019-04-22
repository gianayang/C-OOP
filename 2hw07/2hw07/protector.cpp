#include "protector.h"
#include "noble.h"
using namespace std;


namespace WarriorCraft {
	Protector::Protector(const string& name, int strn):name(name),strength(strn) {} 
	const string& Protector::getName()const { return name; }
	const string& Protector::getLordName()const { return boss->getName(); }
	const int Protector::getStrength()const { return strength; }
	const bool Protector::getHired()const { return boss != nullptr; }
	Warrior::Warrior(const string& name, int strn) : Protector(name, strn) {}
	void Warrior::fight(){}
	Wizard::Wizard(const string& name, int str) : Protector(name, str) {}
	void Wizard::fight() { cout << "POOF! " ; }

	Archer::Archer(const string& name, int str) : Warrior(name, str) {}
	void Archer::fight() { cout << "TWANG! " << Protector::getName() << " says: Take that in the name of my lord,  " << Protector::getLordName() << endl; }

	Swordsman::Swordsman(const string& name, int str) : Warrior(name, str) {}
	void Swordsman::fight() { cout << "CLANG! " << Protector::getName() << " says: Take that in the name of my lord, " << Protector::getLordName() << endl; }

	void Protector::changeStrength(double ratio) {		
		if (ratio == 0.0) {
			strength = 0.0;
		}
		else {
			strength = strength * ratio;
		}
	}

	bool Protector::hires(Lord* noble) {							
		if (boss == nullptr) {
			boss = noble;
			return false;
		}
		else {
			cerr << name << " is already hired!" << endl;
			return true;
		}
	}

	bool Protector::fire() {
		if (boss != nullptr) { //if the warrior is hired, the noble can fire him.
			boss = nullptr;
			return true;
		}
		else {
			cerr << name << " is already fired!" << endl;
			return false;
		}
	}
	void Protector::runaway() {
		if (boss != nullptr) {
			boss->fire(*this);
			boss = nullptr;
		}
	}
}