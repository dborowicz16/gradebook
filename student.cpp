#include "student.hpp"

void Student::add_student(const std::string& new_name) {
    name = new_name;
}

void Student::assign_grade(const std::string& subject, int grade) {
    grades.push_back({subject, grade});
}

std::string Student::get_student() const {
    return name;
}

std::vector<Student::Grade> Student::get_grades() const {
    return grades;
}
