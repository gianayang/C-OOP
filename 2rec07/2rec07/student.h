#include <iostream>
#include <string>
#include <vector>

#ifndef STUDENT_H
#define STUDENT_H
namespace BrooklynPol {
	class Course;
	class Student {
		friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
	public:
		// Student methods needed by Registrar
		Student(const std::string& name);
		const std::string& getName() const;
		void changeName(const std::string& newName);
		bool addCourse(Course*);
		void removedFromCourses();
		// Student method needed by Course
		void removedFromCourse(Course*);

	private:
		std::string name;
		std::vector<Course*> courses;
	};
}
#endif