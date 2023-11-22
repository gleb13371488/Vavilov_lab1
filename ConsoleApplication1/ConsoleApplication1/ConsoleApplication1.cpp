
#include<iostream> 
#include<fstream>
#include<vector>
#include <string>
#include "CompressorStation.h"
#include "Pipe.h"


using namespace std;

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail()	// check type
        || std::cin.peek() != '\n'	// is buffer empty (int/float check)
        || x < min || x > max)		// check range
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Type number (" << min << "-" << max << "):";
    }
    return x;
}

void PrintMenu()
{
    cout << " | Welcome to work panel!Choose any of the provided options if needed or exit the panel :" << endl
        << "1. Enter '1' to ADD a pipe." << endl
        << "2. Enter '2' to ADD a compressor station." << endl
        << "3. Enter '3' to VIEW all the elements." << endl
        << "4. Enter '4' to EDIT a pipe." << endl
        << "5. Enter '5' to EDIT a compressor station." << endl
        << "6. Enter '6' to SAVE a your changes." << endl
        << "7. Enter '7' to LOAD the data from the file." << endl
        << "0. Enter '0' to EXIT the work panel." << endl
        << "Type your answer :";

}


void saveDataToFile(const vector<Pipe>& pipes, const vector<CompressorStation>& stations, const string& pipesFilename, const string& stationsFilename) {
    ofstream pipesFile(pipesFilename);
    if (pipesFile.is_open()) {
        for (const Pipe& pipe : pipes) {
            pipesFile << pipe.name << '\n';
            pipesFile << pipe.length << '\n';
            pipesFile << pipe.diameter << '\n';
            pipesFile << pipe.atWork << '\n';
        }
        pipesFile.close();
        cout << "Pipes data saved: " << pipesFilename << endl;
    }
    else {
        cerr << "File opening error(pipes)." << endl;
    }

    ofstream stationsFile(stationsFilename);
    if (stationsFile.is_open()) {
        for (const CompressorStation& station : stations) {
            stationsFile << station.name << '\n';
            stationsFile << station.totalWorkshops << '\n';
            stationsFile << station.workshopsInOperation << '\n';
            stationsFile << station.efficiency << '\n';
        }
        stationsFile.close();
        cout << "Stations data saved: " << stationsFilename << endl;
    }
    else {
        cerr << "File opening error(stations)." << endl;
    }
}


void loadDataFromFile(vector<Pipe>& pipes, vector<CompressorStation>& stations, const string& pipesFilename, const string& stationsFilename) {
    ifstream pipesFile(pipesFilename);
    if (pipesFile.is_open()) {
        pipes.clear();
        while (!pipesFile.eof()) {
            Pipe pipe;
            getline(pipesFile, pipe.name);
            pipesFile >> pipe.length;
            pipesFile >> pipe.diameter;
            pipesFile >> pipe.atWork;
            pipesFile.ignore();
            if (!pipe.name.empty()) {
                pipes.push_back(pipe);
            }
        }
        pipesFile.close();
        cout << "Pipes data loaded: " << pipesFilename << endl;
    }
    else {
        cerr << "File opening error(pipes)." << endl;
    }

    ifstream stationsFile(stationsFilename);
    if (stationsFile.is_open()) {
        stations.clear();
        while (!stationsFile.eof()) {
            CompressorStation station;
            getline(stationsFile, station.name);
            stationsFile >> station.totalWorkshops;
            stationsFile >> station.workshopsInOperation;
            stationsFile >> station.efficiency;
            stationsFile.ignore();
            if (!station.name.empty()) {
                stations.push_back(station);
            }
        }
        stationsFile.close();
        cout << "Stations data loaded: " << stationsFilename << endl;
    }
    else {
        cerr << "File opening error(stations)." << endl;
    }
}





int main()
{
    vector <Pipe> pipes;
    vector <CompressorStation> stations;
    bool pipeAdded = false;
    bool stationAdded = false;


    while (1)
    {
        PrintMenu();

        switch (GetCorrectNumber(0, 7))
        {
        case 1:
        {
            
            Pipe pipe;
            pipe.read();
            pipes.push_back(pipe);
            break;
        }

        case 2:
        {
            CompressorStation station;
            station.read();
            stations.push_back(station);
            break;
        }
        case 3:
        {
            
            cout << "Pipes:" << endl;
            for (Pipe& pipe : pipes) {
                pipe.display();
            }
            cout << "Compressor stations:" << endl;
            for (CompressorStation& station : stations) {
                station.display();
            }
            break;
            
        }
        case 4:
        {
            if (!pipes.empty()) {
                cout << "Type the name of the editing pipe: ";
                string name;
                cin.ignore();
                getline(cin, name);
                bool found = false;
                for (Pipe& pipe : pipes) {
                    if (pipe.name == name) {
                        pipe.toggleRepair();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "The pipe with the specified name was not found." << endl;
                }
            }
            else {
                cout << "No data on pipes." << endl;
            }
            break;
        }
        case 5:
        {
            if (!stations.empty()) {
                cout << "Enter the name of the COP to edit: ";
                string name;
                cin.ignore();
                getline(cin, name);
                bool found = false;
                for (CompressorStation& station : stations) {
                    if (station.name == name) {
                        int workshopChoice;
                        cout << "Select an action: 1. Start the workshop 2. Stop the Workshop: ";
                        cin >> workshopChoice;
                        switch (workshopChoice) {
                        case 1:
                            station.startWorkshop();
                            break;
                        case 2:
                            station.stopWorkshop();
                            break;
                        default:
                            cout << "Incorrect choice of action." << endl;
                            break;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "A COP with the specified name was not found." << endl;
                }
            }
            else {
                cout << "There is no data on compressor stations." << endl;
            }
            break;
        }
        case 6:
        {
            saveDataToFile(pipes, stations, "pipes.txt", "stations.txt");

            break;
        }
        case 7:
        {
            loadDataFromFile(pipes, stations, "pipes.txt", "stations.txt");
            break;
        }
        case 0:
        {
            return 0;

        }
        default:
        {
            cout << "Wrong action" << endl;
            break;
        }
        }
    }
    return 0;
}

   