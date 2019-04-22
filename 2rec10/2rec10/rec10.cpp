/*
recitation 10:
Topics:
	Inheritance
	Polymorphism
Written by Giana Yang 04/12/2019
*/
#include <iostream>
#include<vector>
#include <string>
using namespace std;


class Instrument {
public:
	virtual void makeSound()const = 0;
	virtual void normalPlay()const = 0;
};
void Instrument::makeSound()const {
	cout << "To make a sound...";
}

class Brass:public Instrument{
public:
	Brass(unsigned num):mouthPiece(num){}
	void makeSound()const {
		Instrument::makeSound();
		cout << " blow on a mouthpiece of size 9" << endl;
	}
private:
	unsigned mouthPiece;
};
class Trumpet :public Brass {
public:
	Trumpet(unsigned num) :Brass(num) {}
	void normalPlay()const {
		cout << "Toot" ;
	}
};
class Trombone :public Brass {
public:
	Trombone(unsigned num):Brass(num){}
	void normalPlay()const {
		cout << "Blat";
	}
};

class String :public Instrument {
public:
	String(unsigned num) :pitch(num) {}
	void makeSound() const{
		cout << "bow a string with pitch 567" << endl;
	}
private:
	unsigned pitch;
};

class Violin :public String {
public:
	Violin(unsigned num):String(num){}
	void normalPlay()const {
		cout << "Screech";
	}
};
class Cello :public String {
public:
	Cello(unsigned num):String(num){}
	void normalPlay()const {
		cout << "Squawk";
	}
};

class Percussion :public Instrument {
public:
	void makeSound() const {
		cout << "hit me" << endl;
	}
};
class Drum :public Percussion {
public:
	Drum(){}
	void normalPlay()const {
		cout << "Boom";
	}
};
class Cymbal :public Percussion {
public:
	Cymbal(){}
	void normalPlay()const {
		cout << "Crash";
	}
};

class Musician {
public:
	Musician() : instr(nullptr) {}

	void acceptInstr(Instrument* instPtr) { instr = instPtr; }

	Instrument* giveBackInstr() {
		Instrument* result(instr);
		instr = nullptr;
		return result;
	}

	void testPlay() const {
		if (instr) instr->makeSound();
		else cerr << "have no instr\n";
	}
	void normalPlay()const {
		if (instr) instr->normalPlay();
		else cerr << "have no instr\n";
	}

private:
	Instrument* instr;
};

class MILL {
public:
	MILL() {}
	void receiveInstr(Instrument& instr) {
		instr.makeSound();
		for (size_t i = 0; i < inventory.size(); ++i) {
			if (inventory[i] == nullptr) {
				inventory[i] = &instr;
				return;
			}
		}
		inventory.push_back(&instr);
	}
	void dailyTestPlay()const {
		for (size_t i = 0; i < inventory.size(); ++i) {
			if (inventory[i] != nullptr) {
				inventory[i]->makeSound();
			}
		}
	}
	Instrument* loanOut() {
		for (size_t i = 0; i < inventory.size(); ++i) {
			if (inventory[i] != nullptr) {
				Instrument* loanInstr = inventory[i];
				inventory[i] = nullptr;
				return loanInstr;
			}
		}
		return nullptr;
	}
private:
	vector<Instrument*>inventory;
};

class Orch {
public:
	Orch(){}
	void addPlayer(Musician& musician){
		for (size_t i = 0; i < orch.size(); ++i) {
			if (&musician == orch[i]) {
				return;
			}
		}
		if (orch.size() <= 25) {
			orch.push_back(&musician);
		}
		else {
			cerr << "Orch is full" << endl;
		}
	}
	void play() const {
		for (size_t i = 0; i < orch.size(); ++i) {
			orch[i]->normalPlay();
		}
		cout << endl;
	}
private:
	vector<Musician*> orch;

};


// PART ONE
int main() {
	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone(4);
	Trumpet trpt(12);
	Violin violin(567);

	MILL mill;
	mill.receiveInstr(trpt);
	mill.receiveInstr(violin);
	mill.receiveInstr(tbone);
	mill.receiveInstr(drum);
	mill.receiveInstr(cello);
	mill.receiveInstr(cymbal);

	Musician bob;
	Musician sue;
	Musician mary;
	Musician ralph;
	Musician jody;
	Musician morgan;

	Orch orch;

	// THE SCENARIO

	//Bob joins the orchestra without an instrument.
	orch.addPlayer(bob);

	//The orchestra performs
	cout << "orch performs\n";
	orch.play();

	//Sue gets an instrument from the MIL2 and joins the orchestra.
	sue.acceptInstr(mill.loanOut());
	orch.addPlayer(sue);

	//Ralph gets an instrument from the MIL2.
	ralph.acceptInstr(mill.loanOut());

	//Mary gets an instrument from the MIL2 and joins the orchestra.
	mary.acceptInstr(mill.loanOut());
	orch.addPlayer(mary);

	//Ralph returns his instrument to the MIL2.
	mill.receiveInstr(*ralph.giveBackInstr());

	//Jody gets an instrument from the MIL2 and joins the orchestra.
	jody.acceptInstr(mill.loanOut());
	orch.addPlayer(jody);

	// morgan gets an instrument from the MIL2
	morgan.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Ralph joins the orchestra.
	orch.addPlayer(ralph);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	// bob gets an instrument from the MIL2
	bob.acceptInstr(mill.loanOut());

	// ralph gets an instrument from the MIL2
	ralph.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Morgan joins the orchestra.
	orch.addPlayer(morgan);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
}
