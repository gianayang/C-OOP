#include <iostream>
#include <string>
#include <vector>

#ifndef REGISTRAR_H
#define REGISTRAR_H
namespace BrooklynPol {
	class Course;
	class Student;
	class Registrar {
		friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
	public:
		Registrar();
		bool addCourse(const std::string&);
		bool addStudent(const std::string&);
		bool enrollStudentInCourse(const std::string& studentName,
			const std::string& courseName);
		bool cancelCourse(const std::string& courseName);
		bool changeStudentName(const std::string& oldName,const std::string& newName);
		bool dropStudentFromCourse(const std::string&stuName, const std::string& courseName);
		bool removeStudent(const std::string& name);
		void purge();

	private:
		size_t findStudent(const std::string&) const;
		size_t findCourse(const std::string&) const;

		std::vector<Course*> courses;
		std::vector<Student*> students;
	};
}


#endif