#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};


void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Enter student name: ";
    std::cin >> student.name;
    std::cout << "Enter student age: ";
    std::cin >> student.age;
    std::cout << "Enter student major: ";
    std::cin >> student.major;
    std::cout << "Enter student GPA: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Student added to database.\n";
}

double calculateAverageAge(const std::vector<Student>& database) {
    if (database.empty()) {
        throw std::runtime_error("Database is empty");
    }
    int sum = 0;
    for (const auto& student : database) {
        sum += student.age;
    }
    return static_cast<double>(sum) / database.size();
}

void displayStudents(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "Database is empty\n";
        return;
    }

    std::cout << "Student list:\n";
    for (const Student& student : database) {
        std::cout << "Name: " << student.name << "\n";
        std::cout << "Age: " << student.age << "\n";
        std::cout << "Major: " << student.major << "\n";
        std::cout << "GPA: " << student.gpa << "\n\n";
    }

    double avg = calculateAverageAge(database);
    std::cout << "Average age of all students: " << avg << "\n";
}

void view() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Display students\n";
        std::cout << "0. Exit\n";
        std::cout << "Select action: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

int main(int argc, char **argv) {
    view();
    return 0;
}