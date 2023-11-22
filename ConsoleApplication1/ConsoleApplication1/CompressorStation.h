#pragma once
#include <iostream>
#include <string>
using namespace std;
class CompressorStation {
public:
    string name;
    int totalWorkshops, workshopsInOperation, efficiency;

    CompressorStation() : name(""), totalWorkshops(0), workshopsInOperation(0), efficiency(0) {}

    void read() {
        cout << "Type the name of the Compressor station: ";
        cin.ignore();
        getline(cin, name);
        cout << "Type the total number of workshops: ";
        cin >> totalWorkshops;
        cout << "Workshops in work: ";
        cin >> workshopsInOperation;
        cout << "Type the efficiency number: ";
        cin >> efficiency;
    }

    void display() {
        cout << "===Registered station detected===\nName: " << name << endl;
        cout << "Total number of workshops: " << totalWorkshops << endl;
        cout << "Workshops in work: " << workshopsInOperation << endl;
        cout << "Efficiency: " << efficiency << endl;
    }

    void startWorkshop() {
        if (workshopsInOperation < totalWorkshops) {
            workshopsInOperation++;
            cout << "Workshop started." << endl;
        }
        else {
            cout << "Too much active workshops." << endl;
        }
    }

    void stopWorkshop() {
        if (workshopsInOperation > 0) {
            workshopsInOperation--;
            cout << "Workshop stopped." << endl;
        }
        else {
            cout << "Not any workshop is active." << endl;
        }
    }
};