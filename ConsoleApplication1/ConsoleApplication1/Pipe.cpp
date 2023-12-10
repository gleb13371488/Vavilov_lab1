#include "Pipe.h"

void Pipe::read() {
    std::cout << "Please, type the name of the pipe: " << name << std::endl;
    std::cout << "Please, type the length: ";
    std::cin >> length;
    std::cout << "Please, type the diameter: ";
    std::cin >> diameter;
    std::cout << "Is pipe functioning? (1 - Yes, 0 - No): ";
    std::cin >> atWork;
}

void Pipe::display() const {
    std::cout << "===Registered pipe detected===\nName: " << name << std::endl;
    std::cout << "Length of the pipe: " << length << std::endl;
    std::cout << "Diameter of the pipe: " << diameter << std::endl;
    std::cout << "Is at work(1 - Yes, 0 - No) " << (atWork ? "Yes" : "No") << std::endl;
}

void Pipe::toggleRepair() {
    atWork = !atWork;
    std::cout << "AtWork status toggled." << std::endl;
}

void Pipe::saveToFile(std::ofstream& file) const {
    file << "Pipe\n";
    file << name << '\n';
    file << length << '\n';
    file << diameter << '\n';
    file << atWork << '\n';
}

bool Pipe::loadFromFile(std::ifstream& file) {
    std::string type;
    std::getline(file, type);
    if (type != "Pipe") {
        std::cerr << "Invalid file format." << std::endl;
        return false;
    }

    std::getline(file, name);
    file >> length;
    file >> diameter;
    file >> atWork;
    file.ignore(); // consume the newline character

    return true;
}