## school.hpp
```cpp
#pragma once
#include "teacher.hpp"
#include "student.hpp"
#include <vector>
class School {
public:
    void enrollStudent(Student* student);
    void hireTeacher(Teacher* teacher);
    void assignStudent(Student* student, Teacher* teacher);
private:
    std::vector<Teacher*> teachers;
    std::vector<Student*> students;
};
```
## school.cpp
```cpp
#include "school.hpp"
void School::enrollStudent(Student* student) {
    students.push_back(student);
}
void School::hireTeacher(Teacher* teacher) {
    teachers.push_back(teacher);
}
void School::assignStudent(Student* student, Teacher* teacher) {
    teacher->addStudent(student);
    student->addTeacher(teacher);
}
```
## student.hpp
```cpp
#include "teacher.hpp"
#include "student.hpp"
void Teacher::assignStudent(Student* student) {
    students.push_back(student);
}
```
## student.cpp
```cpp
#include "teacher.hpp"
#include "student.hpp"
void Teacher::assignStudent(Student* student) {
    students.push_back(student);
}
```
## teacher.hpp
```cpp
#pragma once
#include <string>
#include <vector>
class Student;
class Teacher {
public:
    Teacher(const std::string& name);
    void addStudent(Student* student);
private:
    std::string name;
    std::vector<Student*> students;
};
```
## teacher.cpp
```cpp
#include "teacher.hpp"
#include "student.hpp"
Teacher::Teacher(const std::string& name) : name(name) {}
void Teacher::addStudent(Student* student) {
    students.push_back(student);
}
```
## main.cpp
```cpp
#include "school.hpp"
#include "teacher.hpp"
#include "student.hpp"
#include <iostream>
#include <memory>
int main() {
    School mySchool;
    auto teacher1 = Teacher("Mr. Smith");
    auto student1 = Student("Alice");
    auto student2 = Student("Bob");
    mySchool.hireTeacher(&teacher1);
    mySchool.enrollStudent(&student1);
    mySchool.enrollStudent(&student2);
    mySchool.assignStudent(&student1, &teacher1);
    mySchool.assignStudent(&student2, &teacher1);
    return 0;
}
```