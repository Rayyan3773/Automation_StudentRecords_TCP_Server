#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>  
#include <sstream>
#include "student.h"

std::vector<Student> loadStudents(const std::string &filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return students; // empty vector
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, nameStr, ageStr, gradeStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nameStr, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, gradeStr, ',');

        if (idStr.size() == 0) continue; // skip empty lines

        Student s;
        s.id = std::stoi(idStr);
        s.name = nameStr;
        s.age = std::stoi(ageStr);
        s.grade = gradeStr;

        students.push_back(s);
    }

    return students;
}

void listStudents(const std::vector<Student> &students) {
    std::cout << "---- Student List ----" << std::endl;
    for (const auto &s : students) {
        std::cout << s.id << " " << s.name << " " << s.age << " " << s.grade << std::endl;
    }
}

Student* searchStudentById(std::vector<Student> &students, int id) {
    for (auto &s : students) {
        if (s.id == id) {
            return &s; // return pointer to student
        }
    }
    return nullptr; // not found
}

// sorting

void sortStudentsById(std::vector<Student> &students) {
    std::sort(students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.id < b.id;
        }
    );
}

#endif
