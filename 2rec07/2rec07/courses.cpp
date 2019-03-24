#include "courses.h"
//#include <string>
//#include <vector>
#include "student.h"
using namespace std;

namespace BrooklynPol {
	Course::Course(const string& name) :name(name) {}
	const string& Course::getName() const { return name; }
	bool Course::addStudent(Student* newStudent) {
		for (Student* stu : students) {
			if (stu == newStudent) {
				return false;
			}
		}
		students.push_back(newStudent);
		return true;
	}
	void Course::removeStudentsFromCourse() {
		for (size_t i = 0; i < students.size(); ++i) {
			students[i]->removedFromCourse(this);
		}
		students.clear();
	}
	void Course::removeStudentFromCourse(Student* stu) {
		size_t pos;
		for (size_t i = 0; i < students.size(); ++i) {
			if (stu == students[i]) {
				pos = i;
				break;
			}
		}
		Student* temp;
		for (size_t i = pos; i < students.size() - 1; ++i) {
			temp = students[i];
			students[i] = students[i + 1];
			students[i + 1] = temp;
		}
		students.pop_back();
	}
	ostream& operator<<(ostream& os, const Course& rhs) {
		os << rhs.name << ": ";
		for (const Student* stu : rhs.students) {
			os << stu->getName() << " ";
		}
		if (rhs.students.size() == 0) {
			os << "No students";
		}
		os << endl;
		return os;
	}
}

