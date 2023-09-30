
#include<iostream> 
#include<fstream>
#include<vector>
#include <string>


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
class Pipe {
    public:
        string name;
        int length, diameter;
        bool atWork; 

        Pipe(const string& n, int lenn, int diam, bool work) : name(n), length(lenn), diameter(diam), atWork(work) {}
        
        void change_value() {
            atWork = !atWork;
        }

        void print_info(){
            cout << "===Registered pipe detected===\nName: " << name << "\nLength of the pipe: " << length << "\nDiameter of the pipe: " << diameter << "\nIs at work(1 - Yes, 0 - No): " << atWork << endl;
        }

};

class CompressorStation {
    public:
        string name;
        int numberOfWorkshops, numberOfWorkshopsAtWork, effectiveness;

        CompressorStation(const string& n, int workshops, int workshopsAtWork, int eff) : name(n), numberOfWorkshops(workshops), numberOfWorkshopsAtWork(workshopsAtWork), effectiveness(eff) {}

        void change_value(int nOfWorkshopsAtWork) {
            while (nOfWorkshopsAtWork > numberOfWorkshops){
                cout << "\n\n\n\n\n|----------------------------------------------------------------------------------------|\n\
|   WARNING: The number of workshops wasn't changed, enter a different number.           |\n\
|   Error: Exceeded number of available workshops.                                       |\n\
|----------------------------------------------------------------------------------------|\n\n";

                cout << "Total number of workshops: " << numberOfWorkshops << endl << "Enter the number of number of workshops at work: ";
                cin >> nOfWorkshopsAtWork;
            }
            numberOfWorkshopsAtWork = nOfWorkshopsAtWork;
            
        }

        void print_info(){
            cout << "===Registered station detected===\nName: " << name << "\nNumber of workshops: " << numberOfWorkshops << "\nNumber of workshops at work: " << numberOfWorkshopsAtWork << "\nEffectiveness: " << effectiveness << endl;
        }
};


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



void saveDataToFile(const Pipe& pipe, const CompressorStation& station) {
    ofstream outputFile("data.txt");

    if (outputFile.is_open()) {
        outputFile << "Pipe Data:\n";
        outputFile << "Name: " << pipe.name << "\n";
        outputFile << "Length: " << pipe.length << "\n";
        outputFile << "Diameter: " << pipe.diameter << "\n";
        outputFile << "At Work: " << (pipe.atWork ? "Yes" : "No") << "\n";

        outputFile << "\nCompressor Station Data:\n";
        outputFile << "Name: " << station.name << "\n";
        outputFile << "Number of Workshops: " << station.numberOfWorkshops << "\n";
        outputFile << "Number of Workshops at Work: " << station.numberOfWorkshopsAtWork << "\n";
        outputFile << "Effectiveness: " << station.effectiveness << "\n";

        outputFile.close();
        cout << "Data has been saved to 'data.txt'." << endl;
    }
    else {
        cout << "Unable to open the file for saving." << endl;
    }
}

void loadDataFromFile(Pipe& pipe, CompressorStation& station) {
    ifstream inputFile("data.txt");

    if (inputFile.is_open()) {
        string line;
        string section;  // To keep track of the current section ("Pipe" or "Compressor Station")

        while (getline(inputFile, line)) {
            if (line.empty()) {
                // Skip empty lines
                continue;
            } else if (line == "Pipe Data:") {
                section = "Pipe";
            } else if (line == "Compressor Station Data:") {
                section = "Compressor Station";
            } else {
                // Split the line into key and value
                size_t separatorPos = line.find(':');
                if (separatorPos != string::npos && separatorPos > 0 && separatorPos < line.length() - 1) {
                    string key = line.substr(0, separatorPos);
                    string value = line.substr(separatorPos + 2);  // Skip the space after ':'

                    // Update the corresponding object based on the section
                    if (section == "Pipe") {
                        if (key == "Name") {
                            pipe.name = value;
                        } else if (key == "Length") {
                            pipe.length = stoi(value);
                        } else if (key == "Diameter") {
                            pipe.diameter = stoi(value);
                        } else if (key == "At Work") {
                            pipe.atWork = (value == "Yes");
                        }
                    } else if (section == "Compressor Station") {
                        if (key == "Name") {
                            station.name = value;
                        } else if (key == "Number of Workshops") {
                            station.numberOfWorkshops = stoi(value);
                        } else if (key == "Number of Workshops at Work") {
                            station.numberOfWorkshopsAtWork = stoi(value);
                        } else if (key == "Effectiveness") {
                            station.effectiveness = stoi(value);
                        }
                    }
                }
            }
        }

        inputFile.close();
        cout << "Data has been loaded from 'data.txt'." << endl;
    } else {
        cout << "Unable to open the file for loading." << endl;
    }
}



int main()
{
    vector <Pipe> pipes;
    vector <CompressorStation> compressor_stations;

    Pipe pipe("", 0, 0, false);
    CompressorStation station("", 0, 0, 0);
    bool pipeAdded = false;
    bool stationAdded = false;


    while (1)
    {
        PrintMenu();

        switch (GetCorrectNumber(0, 7))
        {
        case 1:
        {
            bool completion = true;
            string name, atWork;
            int length, diameter;
            bool atWorkBool;
            cout << "Enter the name of the pipe: ";
            cin >> name;
            cout << "Enter the length of the pipe: ";
            cin >> length;
            cout << "Enter the diameter of the Pipe: ";
            cin >> diameter;
            cout << "Enter whether the pipe is currently at work(Y/n):  ";
            cin >> atWork;

            while (completion) {
                if (atWork == "Y") {
                    atWorkBool = true;
                    completion = false;
                }
                else if (atWork == "n") {
                    atWorkBool = false;
                    completion = false;
                }
                else {
                    cout << "Please enter a valid working status(Y/n): ";
                    cin >> atWork;
                }
            }

            pipe = Pipe(name, length, diameter, atWorkBool);
            pipeAdded = true;
            break;
        }


        case 2:
        {
            bool completion = true;
            string name;
            int numberOfWorkshops, numberOfWorkshopsAtWork, effectiveness;

            cout << "Enter the name of the compressor station: ";
            cin >> name;
            cout << "Enter the total number of workshops: ";
            cin >> numberOfWorkshops;
            cout << "Enter the number of workshops at work: ";
            cin >> numberOfWorkshopsAtWork;
            cout << "Enter the effectiveness of the compressor station: ";
            cin >> effectiveness;

            while (completion) {
                if (numberOfWorkshops > numberOfWorkshopsAtWork) {
                    completion = false;
                }
                else {
                    cout << "Number of working workshops can't be more than the total amount. Try again:" << endl;
                    cout << "Enter the total number of workshops: ";
                    cin >> numberOfWorkshops;
                    cout << "\nEnter the number of workshops at work: ";
                    cin >> numberOfWorkshopsAtWork;
                }
            }

            station = CompressorStation(name, numberOfWorkshops, numberOfWorkshopsAtWork, effectiveness);
            stationAdded = true;
            break;
        }
        case 3:
        {
            string continueTheCode;
            if (pipeAdded) {
                pipe.print_info();
            }
            else {
                cout << "\n\n\n\n\n\n Please ADD a pipe";
            }
            if (stationAdded) {
                station.print_info();
            }
            else {
                cout << "\n\n\n\n\n\n Please ADD a station";
            }
            cout << "\n\n\n\n\n\nEnter anything in order to continue: ";
            cin >> continueTheCode;
            break;
        }
        case 4:
        {
            pipe.change_value();
            cout << "Your request was completed." << endl;;
            break;
        }
        case 5:
        {
            string numberAtWork;
            cout << "Enter the new number of stations at work: ";
            cin >> numberAtWork;
            station.change_value(stoi(numberAtWork));
            break;
        }
        case 6:
        {
            saveDataToFile(pipe, station);
            break;
        }
        case 7:
        {
            loadDataFromFile(pipe, station);
            break;
        }
        case 0:
        {
            return 0;

        }
        default:
        {
            cout << "Wrong action" << endl;
        }
        }
    }
    return 0;
}

   