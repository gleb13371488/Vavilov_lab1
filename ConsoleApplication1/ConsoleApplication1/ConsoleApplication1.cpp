#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include <algorithm>
#include "Pipe.h"
#include "CompressorStation.h"
#include "GasNetwork.h"

using namespace std;

int Pipe::idCounter = 0;
int CompressorStation::idCounter = 0;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    istringstream tokenStream(s);
    string token;
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

template <typename T>
void batchAdd(vector<T*>& objects, const vector<string>& names) {
    for (const auto& name : names) {
        T* newObj = new T();
        newObj->name = name;
        newObj->read();
        objects.push_back(newObj);
    }
}

template <typename T>
T GetCorrectNumber(T min, T max) {
    T x;
    while ((cin >> x).fail() || cin.peek() != '\n' || x < min || max < x) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << min << "-" << max << "):";
    }
    return x;
}

vector<Pipe*> searchPipesByName(vector<Pipe*>& pipes, const vector<string>& pipeNames) {
    vector<Pipe*> foundPipes;
    for (const string& name : pipeNames) {
        for (Pipe* pipe : pipes) {
            if (pipe->name == name) {
                foundPipes.push_back(pipe);
            }
        }
    }
    return foundPipes;
}

vector<Pipe*> searchPipesByStatus(vector<Pipe*>& pipes, bool repairStatus) {
    vector<Pipe*> foundPipes;
    for (Pipe* pipe : pipes) {
        if (pipe->atWork == repairStatus) {
            foundPipes.push_back(pipe);
        }
    }
    return foundPipes;
}

vector<CompressorStation*> searchStationsByName(vector<CompressorStation*>& stations, const vector<string>& stationNames) {
    vector<CompressorStation*> foundStations;
    for (const string& name : stationNames) {
        for (CompressorStation* station : stations) {
            if (station->name == name) {
                foundStations.push_back(station);
            }
        }
    }
    return foundStations;
}

vector<CompressorStation*> searchStationsByWorkshopStatus(vector<CompressorStation*>& stations, int inactiveWorkshops) {
    vector<CompressorStation*> foundStations;
    for (CompressorStation* station : stations) {
        if (station->totalWorkshops - station->workshopsInOperation >= inactiveWorkshops) {
            foundStations.push_back(station);
        }
    }
    return foundStations;
}

template<typename T>
void displayElements(vector<T*>& elements) {
    cout << "Found elements:" << endl;
    for (T* element : elements) {
        element->display();
    }
}

template <typename T>
void batchEdit(vector<T*>& elements, const function<void(T*)>& editFunction) {
    if (!elements.empty()) {
        cout << "Do you want to edit the found elements? (1 - Yes, 0 - No): ";
        int editChoice;
        cin >> editChoice;

        if (editChoice == 1) {
            for (T* element : elements) {
                editFunction(element);
            }

            cout << "Batch editing complete." << endl;
        }
    }
}

template<typename T>
void batchDelete(vector<T*>& elements) {
    if (!elements.empty()) {
        cout << "Do you want to delete the found elements? (1 - Yes, 0 - No): ";
        int deleteChoice;
        cin >> deleteChoice;

        if (deleteChoice == 1) {
            elements.clear();
            cout << "Batch deletion complete." << endl;
        }
    }
}

void PrintMenu() {
    cout << " | Welcome to work panel!Choose any of the provided options if needed or exit the panel :" << endl
        << "1. Enter '1' to ADD a pipe or pipes(space separated)." << endl
        << "2. Enter '2' to ADD a compressor station or stations(space separated)." << endl
        << "3. Enter '3' to VIEW all the elements." << endl
        << "4. Enter '4' to EDIT a pipe or pipes." << endl
        << "5. Enter '5' to EDIT a compressor station or stations." << endl
        << "6. Enter '6' to SAVE a your changes." << endl
        << "7. Enter '7' to LOAD the data from the file." << endl
        << "8. Enter '8' to CONNECT a pipe to stations." << endl
        << "9. Enter '9' to PERFORM topological sort on the network." << endl
        << "0. Enter '0' to EXIT the work panel." << endl
        << "Type your answer :";
}

template <typename T>
void saveDataToFile(const vector<T*>& objects, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const T* obj : objects) {
            obj->saveToFile(file);
        }
        file.close();
        cout << "Data saved: " << filename << endl;
    }
    else {
        cerr << "File opening error: " << filename << endl;
    }
}

template <typename T>
void loadDataFromFile(vector<T*>& objects, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        objects.clear();
        while (!file.eof()) {
            T* obj = new T();
            if (obj->loadFromFile(file)) {
                objects.push_back(obj);
            }
            else {
                delete obj;
            }
        }
        file.close();
        cout << "Data loaded: " << filename << endl;
    }
    else {
        cerr << "File opening error: " << filename << endl;
    }
}

template <typename T>
void displayObjects(const vector<T*>& objects) {
    for (const auto& obj : objects) {
        obj->display();
    }
}

int main() {
    vector<Pipe*> pipes;
    vector<CompressorStation*> stations;
    GasNetwork network;

    while (true) {
        PrintMenu();

        int option;
        cin >> option;

        if (option == 0) {
            break;
        }

        switch (option) {
        case 1: {
            cout << "Enter names of pipes(space separated): ";
            string pipeNames;
            cin.ignore();
            getline(cin, pipeNames);
            batchAdd(pipes, split(pipeNames, ' '));
            break;
        }
        case 2: {
            cout << "Enter names of compressor stations(space separated): ";
            string stationNames;
            cin.ignore();
            getline(cin, stationNames);
            batchAdd(stations, split(stationNames, ' '));
            break;
        }
        case 3: {
            cout << "Pipes: " << endl;
            displayObjects(pipes);
            cout << "Compressor Stations: " << endl;
            displayObjects(stations);
            break;
        }
        case 4: {
            cout << "Enter names of pipes to search(space separated): ";
            string pipeNames;
            cin.ignore();
            getline(cin, pipeNames);
            auto foundPipes = searchPipesByName(pipes, split(pipeNames, ' '));
            displayElements(foundPipes);
            batchEdit<Pipe>(foundPipes, [](Pipe* pipe) { pipe->read(); });
            break;
        }
        case 5: {
            cout << "Enter names of stations to search(space separated): ";
            string stationNames;
            cin.ignore();
            getline(cin, stationNames);
            auto foundStations = searchStationsByName(stations, split(stationNames, ' '));
            displayElements(foundStations);
            batchEdit<CompressorStation>(foundStations, [](CompressorStation* station) { station->read(); });
            break;
        }
        case 6: {
            saveDataToFile(pipes, "pipes.txt");
            saveDataToFile(stations, "stations.txt");
            break;
        }
        case 7: {
            loadDataFromFile(pipes, "pipes.txt");
            loadDataFromFile(stations, "stations.txt");
            break;
        }
        case 8: {
            int fromStationId, toStationId, pipeId;
            cout << "Enter ID of the station from where the pipe starts: ";
            cin >> fromStationId;
            cout << "Enter ID of the station where the pipe ends: ";
            cin >> toStationId;
            cout << "Enter ID of the pipe: ";
            cin >> pipeId;
            network.addStation(fromStationId);
            network.addStation(toStationId);
            network.addPipe(pipeId, fromStationId, toStationId);
            break;
        }
        case 9: {
            vector<int> sortedStations = network.topologicalSort();
            cout << "Topological sort result: ";
            for (int stationId : sortedStations) {
                cout << stationId << " ";
            }
            cout << endl;
            break;
        }
        default: {
            cout << "Incorrect option. Try again." << endl;
            break;
        }
        }
    }

    // Освобождаем выделенную память
    for (Pipe* pipe : pipes) {
        delete pipe;
    }
    for (CompressorStation* station : stations) {
        delete station;
    }

    return 0;
}
