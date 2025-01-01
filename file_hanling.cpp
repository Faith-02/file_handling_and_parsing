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
