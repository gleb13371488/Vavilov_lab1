#pragma once
#include <iostream>
#include <string>
#include <fstream>

class CompressorStation {
public:
    static int idCounter;
    int id;
    std::string name;
    int totalWorkshops, workshopsInOperation, efficiency;

    CompressorStation() : id(++idCounter), name(""), totalWorkshops(0), workshopsInOperation(0), efficiency(0) {}

    void read();
    void display() const;
    void startWorkshop();
    void stopWorkshop();
    void saveToFile(std::ofstream& file) const;
    bool loadFromFile(std::ifstream& file);
    void displayDetails() const;
};
