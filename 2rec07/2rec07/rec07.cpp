/*
03/15/2019
 rec07: Seperate Compilation
 focus:
	 Seperate Compilation
	 Namespace
Written by Giana Yang
  
 */

#include <iostream>
#include <string>
#include <vector>
#include "registrar.h"
#include <fstream>
using namespace std;
using namespace BrooklynPol;

void commands(ifstream& file, Registrar& registrar) {
	string command;
	string name1, name2;
	while (file >> command) {
		if (command == "PrintReport") {
			cout << registrar << endl;
		}
		else if (command == "AddCourse") {
			file >> name1;
			registrar.addCourse(name1);

		}
		else if (command == "AddStudent") {
			file >> name1;
			registrar.addStudent(name1);
		}
		else if (command == "EnrollStudentInCourse") {
			file >> name1 >> name2;
			registrar.enrollStudentInCourse(name1, name2);
		}
		else if (command == "CancelCourse") {
			file >> name1;
			registrar.cancelCourse(name2);
		}
		else if (command == "ChangeStudentName") {
			file >> name1 >> name2;
			registrar.changeStudentName(name1, name2);
		}
		else if (command == "DropStudentFromCourse") {
			file >> name1 >> name2;
			registrar.dropStudentFromCourse(name1, name2);

		}
		else if (command == "RemoveStudent") {
			file >> name1;
			registrar.removeStudent(name1);
		}
		else {
			registrar.purge();
		}
	}
}

int main() {
	Registrar registrar;
	ifstream txt("tranction.txt");
	if (!txt) {
		cerr << "cannot open file" << endl;
		exit(1);
	}
	commands(txt, registrar);

	cout << "No courses or students added yet\n";
	cout << registrar << endl;

	cout << "Addcourse cs101.001\n";
	registrar.addCourse("cs101.001");
	cout << registrar << endl;

	cout << "Addstudent fritzthecat\n";
	registrar.addStudent("fritzthecat");
	cout << registrar << endl;

	cout << "Addcourse cs102.001\n";
	registrar.addCourse("cs102.001");
	cout << registrar << endl;

	cout << "Enrollstudentincourse fritzthecat cs102.001\n";
	registrar.enrollStudentInCourse("fritzthecat", "cs102.001");
	cout << "Enrollstudentincourse fritzthecat cs101.001\n";
	registrar.enrollStudentInCourse("fritzthecat", "cs101.001");
	cout << registrar << endl;

	cout << "Enrollstudentincourse bullwinkle cs101.001\n";
	cout << "Should fail, i.e. do nothing, since bullwinkle is not a student.\n";
	registrar.enrollStudentInCourse("bullwinkle", "cs101.001");
	cout << registrar << endl;

	cout << "Cancelcourse cs102.001\n";
	registrar.cancelCourse("cs102.001");
	cout << registrar << endl;


	// [optional - do later if time]
	cout << "Changestudentname fritzthecat mightymouse\n";
	registrar.changeStudentName("fritzthecat", "mightymouse");
	cout << registrar << endl;  // or registrar.printreport()

	cout << "Dropstudentfromcourse mightymouse cs101.001\n";
	registrar.dropStudentFromCourse("mightymouse", "cs101.001");
	cout << registrar << endl;  // or registrar.printreport()

	cout << "Removestudent fritzthecat\n";
	registrar.removeStudent("fritzthecat");
	cout << registrar << endl;  // or registrar.printreport()


	cout << "Purge for start of next semester\n";
	registrar.purge();
	cout << registrar << endl;
}




