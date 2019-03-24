/*
Rec 06: Dynmaic Arrays and Copy Controls
2019/03/08
Focus:
	
    Copy Control (aka Big 3)
    operator[]

Written by Giana Yang
*/

#include <string>
#include <iostream>
using namespace std;

class Position {
	friend ostream& operator<<(ostream& os, const Position& rhs) {
		os << '[' << rhs.title << ',' << rhs.salary << ']';
		return os;
	}
public:
	Position(const string& aTitle, double aSalary)
		: title(aTitle), salary(aSalary) {}
	const string& getTitle() const { return title; }
	double getSalary() const { return salary; }
	void changeSalaryTo(double d) { salary = d; }
private:
	string title;
	double salary;
}; // class Position

class Entry {
	friend ostream& operator<<(ostream& os, const Entry& rhs) {
		os << rhs.name << ' ' << rhs.room
			<< ' ' << rhs.phone << ", " << *rhs.pos;
		return os;
	}
public:
	Entry(const string& name, unsigned room, unsigned phone, Position& position)
		: name(name), room(room), phone(phone), pos(&position) {
	}
	const string& getName() const { return name; }
	unsigned getPhone() const { return phone; }
	/*~Entry() {
		delete pos;
	}*/
private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
}; // class Entry

class Directory {
	// Overload output operator
	friend ostream& operator << (ostream& os, const Directory& dir) {
		os << "Directory:" << endl;
		for (size_t i = 0; i < dir.size; ++i) {
			os << *dir.entries[i] << endl;
		}
		return os;
	}

public:
	// Of course the first function you need to write for this (or
	// any) class is...
	Directory() : capacity(1), size(0), entries(new Entry*[capacity]) {}
	Directory(const Directory& old):capacity(old.capacity),size(old.size) {
		cout << "Using Copy Constructor..." << endl;
		entries = new Entry*[capacity];
		for (size_t i = 0; i < size; ++i) {
			entries[i] = new Entry(*old.entries[i]);
		}
	}

	unsigned operator [](const string&name)const {
		for (size_t i = 0; i < size; ++i) {
			if (entries[i]->getName() == name){
				return entries[i]->getPhone();
			}
		}
		return 99999999;
	}
	// We'll get you started with the add method, but obviously you
	// have a lot of work to do here.
	void add(const string& name, unsigned room, unsigned ph, Position& pos) {
		if (size == capacity) {
			// something is missing!!!  Add it!
			Entry** oldEntry = entries;
			entries = new Entry*[2 * capacity];
			for (size_t i = 0; i < size; ++i) {
				entries[i] = oldEntry[i];
			}
			capacity *= 2;
			delete[] oldEntry;
			
		} // if
		entries[size] = new Entry(name, room, ph, pos);
		++size;
	} // add

	Directory& operator = (const Directory& rhs) {
		cout << "Using assignment operator" << endl;
		for (size_t i = 0; i < size; ++i) {
			delete entries[i];
		}
		delete[] entries;
		entries = new Entry*[rhs.capacity];
		for (size_t i = 0; i < rhs.size; ++i) {
			entries[i] = new Entry(*rhs.entries[i]);
		}
		capacity = rhs.size;
		size = rhs.size;
		return *this;
	}

	~Directory() {
		cout << "Deleting every Entry" << endl;
		for (size_t i = 0; i <size; ++i ) {
			delete entries[i];
		}
		cout << "Deleting entries" << endl;
		delete [] entries;
	}
	

private:
	size_t capacity;
	size_t size;
	Entry** entries;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {

	// Note that the Postion objects are NOT on the heap.
	Position boss("Boss", 3141.59);
	Position pointyHair("Pointy Hair", 271.83);
	Position techie("Techie", 14142.13);
	Position peon("Peonissimo", 34.79);

	// Create a Directory
	Directory d;
	d.add("Marilyn", 123, 4567, boss);
	cout << d << endl;

	Directory d2 = d;	// What function is being used??
	d2.add("Gallagher", 111, 2222, techie);
	d2.add("Carmack", 314, 1592, techie);
	cout << d << endl;
	cout << d2 << endl;
	/*Directory d4(d);
	cout << d4 << endl;*/

	cout << "Calling doNothing\n";
	doNothing(d2);
	cout << "Back from doNothing\n";

	Directory d3;
	d3 = d2;

	// Should display 1592
	cout << d2["Carmack"] << endl;
} // main

