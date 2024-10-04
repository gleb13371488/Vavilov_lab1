#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Pipe {
public:
    static int idCounter;
    int id;
    std::string name;
    int length, diameter;
    bool atWork;

    Pipe() : id(++idCounter), name(" "), length(0), diameter(0), atWork(false) {}

    void read();
    void display() const;
    void toggleRepair();
    void saveToFile(std::ofstream& file) const;
    bool loadFromFile(std::ifstream& file);
    void displayDetails() const;
};
