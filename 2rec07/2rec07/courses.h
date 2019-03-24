#include <iostream>
#include <string>
#include <vector>
#ifndef COURSES_H
#define COURSES_H
namespace BrooklynPol {
	class Student;

	class Course {
		friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
	public:
		// Course methods needed by Registrar
		Course(const std::string& courseName);
		const std::string& getName() const;
		bool addStudent(Student*);
		void removeStudentsFromCourse();
		void removeStudentFromCourse(Student*);
	private:
		std::string name;
		std::vector<Student*> students;
	};
}
#endif 

