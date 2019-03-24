//#include <iostream>
//#include <string>
//#include <vector>
#include "courses.h"
#include "student.h"
using namespace std;

namespace BrooklynPol {
	Student::Student(const string& name) : name(name) {}
	const string& Student::getName() const { return name; }
	void Student::changeName(const std::string& newName) { name = newName; }
	bool Student::addCourse(Course*newCourse) {
		for (Course* course : courses) {
			if (course == newCourse) {
				return false;
			}
		}
		courses.push_back(newCourse);
		return true;
	}
	void Student::removedFromCourse(Course*delCourse) {
		size_t pos;
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i] == delCourse) {
				pos = i;
				break;
			}
		}
		for (size_t i = pos; i < courses.size() - 1; ++i) {
			Course* temp = courses[i];
			courses[i] = courses[i + 1];
			courses[i + 1] = temp;
		}
		courses.pop_back();
	}
	void Student::removedFromCourses() {
		for (size_t i = 0; i < courses.size(); ++i) {
			courses[i]->removeStudentFromCourse(this);
			delete courses[i];
		}
		courses.clear();
	}
	ostream& operator<<(ostream& os, const Student& rhs) {
		os << rhs.name << ":";
		for (Course* course : rhs.courses) {
			os << course->getName() << " ";
		}
		if (rhs.courses.size() == 0) {
			os << "No Courses";
		}
		os << endl;
		return os;
	}
}