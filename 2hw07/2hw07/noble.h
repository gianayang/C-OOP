#include <iostream>
#include <string>
#include <vector>
#ifndef NOBLE_H
#define NOBLE_H

namespace WarriorCraft {
	class Protector;
	class Noble {
	public:
		Noble(const std::string& name);
		const std::string& getName()const;//grand access for subclass
		void battle(Noble& enemy);//change strength and output reseults
		bool getStatus()const;//if noble is dead
		virtual void changeStrength(double) = 0; //pass in 0 if the noble is going to die
	private:
		std::string name;
		bool dead = false;
		virtual double calculateStrength()const=0;//all the subclass need to have a calculateStrength method
		virtual void fight()const = 0;//all sub class need to fight
		
	};
	class PersonWithStrengthToFight : public Noble {
	public:
		PersonWithStrengthToFight(std::string name, int strength);
		void changeStrength(double);//change strength with the ratio
		
	private:
		double calculateStrength()const;//return strength
		double strength;
		void fight()const;//yell out the words
	};
	class Lord : public Noble {
	public:
		Lord(const std::string& name);
		bool hires(Protector& protector);
		void fire(Protector& warrior);
		void changeStrength(double ratio);//change each strength according to the ratio
	private:
		std::vector<Protector*> army;
		void fight()const;//have each in the army to yell out the words
		double calculateStrength()const; //measuring army strength for the battle
	};
}
#endif // !NOBLE_H
