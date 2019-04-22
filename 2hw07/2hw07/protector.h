#include <iostream>
#include <string>
#include <vector>
#ifndef PROTECTOR_H
#define PROTECTOR_H

namespace WarriorCraft{
	class Lord;
	class Protector {
	public:
		Protector(const std::string& name, int strn);//constructor that takes in a string and a double
		virtual void fight() = 0; //pure virtual for yelling out words during the fight
		const std::string& getName()const;//for sub class to access name
		const std::string& getLordName()const;//access boss name for the fight function
		const bool getHired()const;//return a bool for if already hired
		void changeStrength(double ratio);//change strength after the fight,pass in 0.0 if it's deafeated
		const int getStrength()const; //for noble to access to calculate the army's strength
		void runaway();//escape from the army, change boss to nullptr
		bool hires(Lord* noble); //to see if the warrior is already hired,change the state of hiring
		bool fire();//got fired, change boss to nullptr
	private:
		std::string name;
		int strength;
		Lord* boss = nullptr;
	};

	class Wizard :public Protector {
	public:
		Wizard(const std::string& name, int str);
		void fight();//yell out the words
	};

	class Warrior :public Protector {
	public:
		Warrior(const std::string& name, int str);
		void fight();//yell out the words
	};
	class Archer :public Warrior {
	public:
		Archer(const std::string& name, int str);
		void fight();//yell out the words
	};
	class Swordsman :public Warrior {
	public:
		Swordsman(const std::string& name, int str);
		void fight();//yell out the words
	};
}


#endif // !PROTECTOR_H