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
void addStudent(const string& filename) {
    Student student;
    cout << "Enter Student ID: ";
    cin >> student.id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter Student Age: ";
    cin >> student.age;
    cout << "Enter Student Grade: ";
    cin >> student.grade;

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << student.toCSV() << endl;
        cout << "Student added successfully!" << endl;
    } else {
        cout << "Failed to open file." << endl;
    }
    file.close();
}

void viewStudents(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        cout << "Student Records:" << endl;
        cout << "ID\tName\t\tAge\tGrade" << endl;
        cout << "----------------------------------------" << endl;
        while (getline(file, line)) {
            Student student = Student::fromCSV(line);
            cout << student.id << "\t" << student.name << "\t" << student.age << "\t" << student.grade << endl;
        }
    } else {
        cout << "Failed to open file." << endl;
    }
    file.close();
}

void searchStudent(const string& filename) {
    cout << "Enter Student ID to search: ";
    string id;
    cin >> id;

    ifstream file(filename);
    