#include <iostream> 
#include <fstream> 
#include <string> 
#include <ctime> 

using namespace std; 

int main() {
    string name, extraInfo, line; 
    char action, choice; 

    do {
        cout << "\nWould you like to (W)rite a new entry or (R)ead a File? ";
        cin >> action; 
        cout << "Name: "; 
        cin >> name; 

        string fileName = name + ".txt";

        if (action == 'r' || action == 'R') {
            ifstream inFile(fileName);
            if (inFile.is_open()) {
                cout << "\n--- Viewing File: " << fileName << " ---\n"; 
                while (getline(inFile, line)) {
                    cout << line << endl;
                }
                inFile.close();
            } else {
                cout << "No record found for " << name << endl; 
            }
        } 
        else {
            ifstream checkFile(fileName);
            bool isNewFile = !checkFile.is_open();
            checkFile.close();

            ofstream outFile(fileName, ios::app);

            if (outFile.is_open()) {
                time_t now = time(0); 
                string dt = ctime(&now); 
                dt.pop_back(); 

                if (isNewFile) {
                    outFile << "Name: " << name << endl; 
                    outFile << "-----------------" << endl; 
                }
                
                cout << "What would you like to add to " << name << "'s file? ";
                getline(cin >> ws, extraInfo);

                outFile << "[" << dt << "]" << endl;
                outFile << extraInfo << endl; 
                outFile << "-----------------" << endl; 
                outFile.close(); 
                cout << "Info saved with timestamp!" << endl; 
            } else {
                cerr << "Error opening file!" << endl; 
            }
        }

        // --- Crucial Addition: Ask to continue ---
        cout << "\nWould you like to perform another action? (y/n): ";
        cin >> choice; 

    } while (choice == 'y' || choice == 'Y');

    return 0;
}