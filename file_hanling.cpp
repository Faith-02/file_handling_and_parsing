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
    if (file.is_open()) {
        string line;
        bool found = false;
        while (getline(file, line)) {
            Student student = Student::fromCSV(line);
            if (student.id == id) 
            {
                cout << "Student Found:" << endl;
                cout << "ID: " << student.id << endl;
                cout << "Name: " << student.name << endl;
                cout << "Age: " << student.age << endl;
                cout << "Grade: " << student.grade << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found." << endl;
        }
    } else {
        cout << "Failed to open file." << endl;
    }
    file.close();
}

void deleteStudent(const string& filename) {
    cout << "Enter Student ID to delete: ";
    string id;
    cin >> id;

    ifstream file(filename);
    ofstream tempFile("temp.txt");
    if (file.is_open() && tempFile.is_open()) {
        string line;
        bool deleted = false;
        while (getline(file, line)) {
            Student student = Student::fromCSV(line);
            if (student.id == id) {
                deleted = true;
                continue; // Skip writing this record
            }
            tempFile << line << endl;
        }
        file.close();
        tempFile.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (deleted) {
            cout << "Student with ID " << id << " deleted successfully!" << endl;
        } else {
            cout << "Student with ID " << id << " not found." << endl;
        }
    } else {
        cout << "Failed to open file." << endl;
    }
}

int main() {
    const string filename = "students.txt";
    int choice;
do {
      cout << "\nStudent Database System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. View Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(filename);
                break;
            case 2:
                viewStudents(filename);
                break;
            case 3:
                searchStudent(filename);
                break;
            case 4:
                deleteStudent(filename);
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    
}

