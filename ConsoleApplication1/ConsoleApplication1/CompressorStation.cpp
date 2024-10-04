#include "CompressorStation.h"

void CompressorStation::read() {
    std::cout << "Type the name of the Compressor station: " << name << std::endl;
    std::cout << "Type the total number of workshops: ";
    std::cin >> totalWorkshops;
    std::cout << "Workshops in work: ";
    std::cin >> workshopsInOperation;
    std::cout << "Type the efficiency number: ";
    std::cin >> efficiency;
}

void CompressorStation::display() const {
    std::cout << "===Registered station detected===\nName: " << name << std::endl;
    std::cout << "Total number of workshops: " << totalWorkshops << std::endl;
    std::cout << "Workshops in work: " << workshopsInOperation << std::endl;
    std::cout << "Efficiency: " << efficiency << std::endl;
}

void CompressorStation::startWorkshop() {
    if (workshopsInOperation < totalWorkshops) {
        workshopsInOperation++;
        std::cout << "Workshop started." << std::endl;
    }
    else {
        std::cout << "Too much active workshops." << std::endl;
    }
}

void CompressorStation::stopWorkshop() {
    if (workshopsInOperation > 0) {
        workshopsInOperation--;
        std::cout << "Workshop stopped." << std::endl;
    }
    else {
        std::cout << "Not any workshop is active." << std::endl;
    }
}

void CompressorStation::saveToFile(std::ofstream& file) const {
    file << "CompressorStation\n";
    file << name << '\n';
    file << totalWorkshops << '\n';
    file << workshopsInOperation << '\n';
    file << efficiency << '\n';
}

bool CompressorStation::loadFromFile(std::ifstream& file) {
    std::string type;
    std::getline(file, type);
    if (type != "CompressorStation") {
        std::cerr << "Invalid file format." << std::endl;
        return false;
    }

    std::getline(file, name);
    file >> totalWorkshops;
    file >> workshopsInOperation;
    file >> efficiency;
    file.ignore(); // consume the newline character

    return true;
}
