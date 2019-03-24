#include <iostream>
#include <vector>
#include <string>


#ifndef WARRIOR_H
#define WARRIOR_H
namespace WarriorCraft {
	class Noble;
	class Warrior {
		friend std::ostream& operator<< (std::ostream& os, const Warrior& warrior);
	public:
		Warrior(const std::string&, int);
		double getStrength()const;
		bool getHired()const;
		const std::string& getName()const;
		bool hire(Noble* noble);
		bool fire();
		void changeStrength(double harm);
		void changeStrengthtoZero();
		void runaway();
	private:
		double strength;
		std::string name;
		Noble* boss = nullptr;
	};
}

#endif // !

