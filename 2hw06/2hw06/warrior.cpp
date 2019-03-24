#include "warrior.h"
#include "noble.h"
using namespace std;

namespace WarriorCraft {
	Warrior::Warrior(const string& name, int str) :name(name), strength(str) {}
	double Warrior::getStrength()const { return strength; }  //get the strength for status display
	bool Warrior::getHired()const { return boss != nullptr; } //get access to hire status for "unemployeed"
	const string& Warrior::getName()const { return name; } //get access to name for "unemployeed"status
	bool Warrior::hire(Noble* noble) {							//to see if the warrior is already hired,change the state of hiring
		if (boss == nullptr) {
			boss = noble;
			return false;
		}
		else {
			cerr << name << " is already hired!" << endl;
			return true;
		}
	}
	bool Warrior::fire() {
		if (boss != nullptr) { //if the warrior is hired, the noble can fire him.
			boss = nullptr;
			return true;
		}
		else {
			cerr << name << " is already fired!" << endl;
			return false;
		}
	}

	void Warrior::changeStrength(double harm) {				//take the percentage of harm and change the strength to after battle
		strength = strength * harm;
	}
	void Warrior::changeStrengthtoZero() {  //dead 
		strength = 0;
	}
	void Warrior::runaway() {
		boss->fire(*this);
		boss = nullptr;
	}
	ostream& operator << (ostream& os, const Warrior& warrior) {   //output operator to display the status
		os << "	" << warrior.getName() << ": " << warrior.getStrength() << endl;
		return os;
	}
}

