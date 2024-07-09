#include <iostream>
#include <string>
#include <vector>

class Student {
    std::string name;
    struct Grade {
        std::string subject;
        int grade;
    };
    std::vector<Grade> grades;

public:
    void add_student(const std::string& new_name);
    void assign_grade(const std::string& subject, int grade);
    std::string get_student() const;
    std::vector<Grade> get_grades() const;
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Name: " << student.name << "\nGrades:\n";
        for (const auto& grade : student.grades) {
            os << "{ subject: " << grade.subject << ", grade: " << grade.grade << " }\n";
        }
        return os;
    }
};
