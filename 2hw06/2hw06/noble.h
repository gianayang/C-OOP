#include <iostream>
#include <vector>
#include <string>

#ifndef NOBLE_H
#define NOBLE_H
namespace WarriorCraft {
	class Warrior;
	class Noble {
		friend std::ostream& operator << (std::ostream& os, const Noble& noble);

	public:
		Noble(const std::string& name);
		const std::string& getName() const;
		void battle(Noble& enemy);
		bool hire(Warrior& warrior);
		void fire(Warrior& warrior);

	private:
		std::string name;
		bool dead = false;
		std::vector<Warrior*> army;
		double calculateStrength()const;
	};

}
#endif // !NOBLE_H
