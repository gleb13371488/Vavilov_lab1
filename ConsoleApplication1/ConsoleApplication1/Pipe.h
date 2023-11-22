#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pipe {
public:
    string name;
    int length, diameter;
    bool atWork;

    Pipe() : name(""), length(0), diameter(0), atWork(false) {}

    void read() {
        cout << "Please, type the name of the pipe: ";
        cin.ignore();
        getline(cin, name);
        cout << "Please, type the length: ";
        cin >> length;
        cout << "Please, type the diameter: ";
        cin >> diameter;
        cout << "Is pipe functioning? (1 - Yes, 0 - No): ";
        cin >> atWork;
    }

    void display() {
        cout << "===Registered pipe detected===\nName: " << name << endl;
        cout << "Length of the pipe: " << length << endl;
        cout << "Diameter of the pipe: " << diameter << endl;
        cout << "Is at work(1 - Yes, 0 - No) " << (atWork ? "Yes" : "No") << endl;
    }

    void toggleRepair() {
        atWork = !atWork;
        cout << "AtWork status toggled." << endl;
    }
};