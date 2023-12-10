
#include<iostream> 
#include<fstream>
#include<vector>
#include <sstream>
#include <algorithm>
#include <string>
#include "CompressorStation.h"
#include "Pipe.h"


using namespace std;

int Pipe::idCounter = 0;
int CompressorStation::idCounter = 0;


// Разделение строки по пробелам
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(s);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

template <typename T>
vector<T*> searchByName(const vector<T>& objects, const string& name)
{
    vector<T*> result;
    for (auto& obj : objects)
    {
        if (obj->name == name)
        {
            result.push_back(obj);
        }
    }
    return result;
}

template <typename T>
vector<T*> searchByStatus(const vector<T>& objects, bool status)
{
    vector<T*> result;
    for (auto& obj : objects)
    {
        if (obj->atWork == status && typeid(obj) == typeid(Pipe))
        {
            result.push_back(obj);
        }
        else if (obj->workshopsInOperation == status && typeid(obj) == typeid(CompressorStation))
        {
            result.push_back(obj);
        }
    }
    return result;
}

template <typename T>
void batchEdit(vector<T*>& objects, const string& name, bool status)
{
    for (auto& obj : objects)
    {
        if (obj->name == name)
        {
            obj->atWork = status;
            obj->workshopsInOperation = status;
        }
    }
}

template <typename T>
void batchAdd(std::vector<T*>& objects, const std::vector<std::string>& names) {
    for (const auto& name : names) {
        T* newObj = new T();
        newObj->name = name; // Устанавливаем имя
        newObj->read();
        objects.push_back(newObj);
    }
}

template <typename T>
void batchDelete(vector<T*>& objects, const string& name)
{
    auto it = remove_if(objects.begin(), objects.end(), [&](T* obj) {
        return obj->name == name;
        });

    for (auto iter = it; iter != objects.end(); ++iter)
    {
        delete* iter;
    }

    objects.erase(it, objects.end());
}

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
        << "1. Enter '1' to ADD a pipe or pipes(space separated)." << endl
        << "2. Enter '2' to ADD a compressor station or stations(space separated)." << endl
        << "3. Enter '3' to VIEW all the elements." << endl
        << "4. Enter '4' to EDIT a pipe or pipes." << endl
        << "5. Enter '5' to EDIT a compressor station or stations." << endl
        << "6. Enter '6' to SAVE a your changes." << endl
        << "7. Enter '7' to LOAD the data from the file." << endl
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

// Функция загрузки данных из файла
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
void displayObjects(const vector<T*>& objects)
{
    for (const auto& obj : objects)
    {
        obj->display();
    }
}




int main()
{
    vector <Pipe*> pipes;
    vector <CompressorStation*> stations;
    


    while (1)
    {
        PrintMenu();

        switch (GetCorrectNumber(0, 7))
        {
        case 1:
        {
            
            cout << "Enter the names of pipes to add (space-separated): ";
            string namesToAdd;
            cin.ignore();
            getline(cin, namesToAdd);

            vector<string> pipeNames = split(namesToAdd, ' ');

            batchAdd(pipes, pipeNames);
            break;
        }

        case 2:
        {
            cout << "Enter the names of compressor stations to add (space-separated): ";
            string namesToAdd;
            cin.ignore();
            getline(cin, namesToAdd);

            vector<string> stationNames = split(namesToAdd, ' ');

            batchAdd(stations, stationNames);
            break;
        }
        case 3:
        {
            cout << "Pipes:" << endl;
            for (const Pipe* pipe : pipes) {
                pipe->displayDetails();
            }

            cout << "Compressor stations:" << endl;
            for (const CompressorStation* station : stations) {
                station->displayDetails();
            }
            break;
        }
        /*case 4:
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
        }*/
        /*case 5:
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
        }*/
        case 6:
        {
            string filename;
            cout << "Enter the filename to save data: ";
            cin >> filename;

            // Сохраняем данные в файл
            saveDataToFile(pipes, filename + "_pipes.txt");
            saveDataToFile(stations, filename + "_stations.txt");

            break;
        }
        case 7:
        {
            string filename;
            cout << "Enter the filename to load data: ";
            cin >> filename;

            // Загружаем данные из файла
            loadDataFromFile(pipes, filename + "_pipes.txt");
            loadDataFromFile(stations, filename + "_stations.txt");

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

   