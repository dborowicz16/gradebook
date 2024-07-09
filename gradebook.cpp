#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

#include "student.hpp"

void make_choice();
void ask_if_done();
void enroll_student();
void view_student();
void remove_student();
void assign_grade();

std::vector<Student> student_list;

void make_choice()
{
    std::cout << "What would you like to do? \n"
              << "[1] Add Student \n"
              << "[2] View Student \n"
              << "[3] Remove Student \n"
              << "[4] Assign Grade \n";

    int choice;

    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The input must be a number. \n";
    }

    switch (choice)
    {
    case 1:
        std::cout << "\n";
        enroll_student();
        break;
    case 2:
        std::cout << "\n";
        view_student();
        break;
    case 3:
        std::cout << "\n";
        remove_student();
        break;
    case 4:
        std::cout << "\n";
        assign_grade();
        break;
    default:
        std::cout << "\n";
        std::cout << "You did not enter a valid option \n";
        make_choice();
    };
}

void ask_if_done()
{
    int choice;
    std::cout << "Do you want to close the gradebook or keep using it? \n"
              << "[1] Close the gradebook \n"
              << "[2] Keep using gradebook \n";
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The input must be a number. \n";
    }

    if (choice == 1)
    {
        std::cout << "You close the gradebook. \n";
    }
    else if (choice == 2)
    {
        make_choice();
    }
    else
    {
        std::cout << "You did not enter a valid option \n";
        ask_if_done();
    }
}

void enroll_student()
{
    std::string student_name;
    std::cout << "What is the student's name? \n";
    std::cin >> student_name;

    std::cout << "You entered the name: " << student_name << "\nIs that correct?\n";
    std::cout << "[1] Yes, " << student_name << " is correct! \n"
              << "[2] No, I made a typo! \n";
    int choice;
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The input must be a number. \n";
    }

    if (choice == 1)
    {
        Student student;
        student.add_student(student_name);
        student_list.emplace_back(student);

        std::cout << "Okay! " << student.get_student() << " is added to the database \n";

        ask_if_done();
    }
    else if (choice == 2)
    {
        std::cout << "Okay! No worries, let's try again! \n";
        enroll_student();
    }
    else
    {
        std::cout << "You did not enter a valid option. Let's try again! \n";
        enroll_student();
    }
}

void view_student()
{
    std::string student_name;
    std::cout << "What is the name of the student that you are trying to view grades for? \n";
    std::cin >> student_name;
    auto it = std::find_if(student_list.begin(), student_list.end(),
                           [&student_name](const Student &student)
                           {
                               return student.get_student() == student_name;
                           });

    if (it != student_list.end())
    {
        std::cout << "Okay! Here is the gradebook information on " << student_name << " \n";
        std::cout << *it << std::endl;
        ask_if_done();
    }
    else
    {
        std::cout << "Student not found.\n";
        view_student();
    }
}

void remove_student()
{
    std::string student_name;
    int choice;
    std::cout << "What is the name of the student that you are trying to remove? \n";
    std::cin >> student_name;
    std::cout << "Are you sure you want to remove " << student_name << " from the gradebook? \n";
    std::cout << "[1] Yes \n"
              << "[2] No \n";
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The input must be a number. \n";
    }

    if (choice == 1)
    {
        auto it = std::find_if(student_list.begin(), student_list.end(), [&student_name](const Student &student)
                               { return student.get_student() == student_name; });

        if (it != student_list.end())
        {
            std::cout << student_name << " has been removed from the gradebook. \n";
            int index = std::distance(student_list.begin(), it);
            student_list.erase(student_list.begin() + index);
            ask_if_done();
        }
        else
        {
            std::cout << "Student not found." << std::endl;
            remove_student();
        }
    }
    else if (choice == 2)
    {
        remove_student();
    }
    else
    {
        std::cout << "You did not enter a valid option. Let's try again! \n";
        remove_student();
    }
}

void assign_grade()
{
    std::cout << "Who will the grade be assigned to? \n";
    std::string student_name;
    std::cin >> student_name;
    std::cout << "You entered the name: " << student_name << "\nIs that correct?\n";
    std::cout << "[1] Yes, " << student_name << " is correct! \n"
              << "[2] No, I made a typo! \n";
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        std::string subject;
        std::cout << "What is the subject? \n";
        std::cin >> subject;
        std::cout << "What is the grade? \n";
        int grade;
        std::cin >> grade;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "The grade must be a number. \n"
                      << "For example: 92 \n";
            
            assign_grade();
        }

        auto it = std::find_if(student_list.begin(), student_list.end(), [&student_name](const Student &student)
                               { return student.get_student() == student_name; });

        if (it != student_list.end())
        {
            int index = std::distance(student_list.begin(), it);
            std::cout << "Student " << student_name << " found" << std::endl;
            student_list[index].assign_grade(subject, grade);
            make_choice();
        }
        else
        {
            std::cout << "Student not found." << std::endl;
            assign_grade();
        }
    }
    else if (choice == 2)
    {
        std::cout << "Okay! No worries, let's try again! \n";
        assign_grade();
    }
    else
    {
        std::cout << "You did not enter a valid option. Let's try again! \n";
        assign_grade();
    }
}

int main()
{
    std::cout << "Hello! Welcome to the gradebook. \n";
    enroll_student();
}