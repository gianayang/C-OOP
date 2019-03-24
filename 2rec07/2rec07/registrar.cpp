//#include <iostream>
//#include <string>
//#include <vector>
#include "courses.h"
#include "student.h"
#include "registrar.h"
using namespace std;


namespace BrooklynPol {
	Registrar::Registrar() {}
	ostream& operator<<(ostream& os, const Registrar& rhs) {
		os << "Registrar's Report" << endl;
		os << "Courses:" << endl;
		for (Course* course : rhs.courses) {
			os << *course;
		}
		os << "Students:" << endl;
		for (Student* stu : rhs.students) {
			os << *stu;
		}
		return os;
	}
	bool Registrar::addCourse(const string& course) {
		if (findCourse(course) == courses.size()) {
			Course* newC = new Course(course);
			courses.push_back(newC);
			return true;
		}
		return false;
	}
	bool Registrar::addStudent(const string&stu) {
		if (findStudent(stu) == students.size()) {
			Student* newC = new Student(stu);
			students.push_back(newC);
			return true;
		}
		return false;
	}

	bool Registrar::enrollStudentInCourse(const string& studentName,
		const string& courseName) {
		size_t pos = findStudent(studentName);
		size_t coursePos = findCourse(courseName);
		if (pos == students.size() || coursePos == courses.size()) {
			return false;
		}
		return students[pos]->addCourse(courses[coursePos]) &&
			courses[coursePos]->addStudent(students[pos]);
	}

	bool Registrar::cancelCourse(const string& courseName) {
		size_t pos = findCourse(courseName);
		if (pos == courses.size()) {
			cerr << "Course does not exist" << endl;
			return false;
		}
		courses[pos]->removeStudentsFromCourse();
		for (size_t i = pos; i < courses.size() - 1; ++i) {
			Course* temp = courses[i];
			courses[i] = courses[i + 1];
			courses[i + 1] = temp;
		}
		delete courses[courses.size() - 1];
		courses.pop_back();
		return true;
	}
	void Registrar::purge() {
		for (size_t i = 0; i < students.size(); ++i) {
			delete students[i];
		}
		students.clear();
		for (size_t i = 0; i < courses.size(); ++i) {
			delete courses[i];
		}
		courses.clear();
	}
	bool Registrar::changeStudentName(const std::string& oldName, const std::string& newName) {
		size_t pos = findStudent(oldName);
		if (pos != students.size()) {
			students[pos]->changeName(newName);
			return true;
		}
		return false;
	}
	bool Registrar::dropStudentFromCourse(const std::string&stuName, const std::string& courseName) {
		size_t pos = findStudent(stuName);
		size_t coursePos = findCourse(courseName);
		if (pos != students.size() && coursePos != courses.size()) {
			students[pos]->removedFromCourse(courses[coursePos]);
			courses[coursePos]->removeStudentFromCourse(students[pos]);
			return true;
		}
		return false;
	}
	bool Registrar::removeStudent(const std::string& name) {
		size_t pos = findStudent(name);
		if (pos == students.size()) {
			cerr << "Student does not exist" << endl;
			return false;
		}
		students[pos]->removedFromCourses();
		for (size_t i = pos; i < students.size() - 1; ++i) {
			Student* temp = students[i];
			students[i] = students[i + 1];
			students[i + 1] = temp;
		}
		delete students[students.size() - 1];
		students.pop_back();
		return true;
	}

	size_t Registrar::findStudent(const string&stu) const {
		for (size_t i = 0; i < students.size(); ++i) {
			if (students[i]->getName() == stu) {
				return i;
			}
		}
		return students.size();
	}
	size_t Registrar::findCourse(const string& newcourse) const {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i]->getName() == newcourse) {
				return i;
			}
		}
		return courses.size();
	}
}