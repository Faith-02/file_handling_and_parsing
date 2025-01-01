#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string id;
    string name;
    int age;
    string grade;

    string toCSV() const {
        return id + "," + name + "," + to_string(age) + "," + grade;
    }

    static Student fromCSV(const string& csvLine) {
        Student student;
        stringstream ss(csvLine);
        getline(ss, student.id, ',');
        getline(ss, student.name, ',');
        ss >> student.age;
        ss.ignore(1, ','); 
        getline(ss, student.grade);
        return student;
    }
};
