#ifndef RECYCLESYSTEM_H
#define RECYCLESYSTEM_H

#include <iostream>
#include <limits>
#include <algorithm> 
#include "WasteList.h"

using namespace std;

class RecycleSystem {
private:
    WasteList* generalBin; 
    WasteList* plasticBin; 
    WasteList* glassBin;   
    WasteList* paperBin;   

    string toLower(string str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

public:
    RecycleSystem() {
        generalBin = new WasteList("General Waste (Stack)", true);
        
        plasticBin = new WasteList("Plastic (Queue)", false);
        glassBin   = new WasteList("Glass (Queue)", false);
        paperBin   = new WasteList("Paper (Queue)", false);
    }

    ~RecycleSystem() {
        delete generalBin; delete plasticBin; delete glassBin; delete paperBin;
        cout << "[System] Recycle System Shutdown Complete." << endl;
    }

    void run() {
        int choice;
        do {
            cout << "\n========================================" << endl;
            cout << "    SMART RECYCLE CENTER (V.2.0)    " << endl;
            cout << "========================================" << endl;
            cout << " [1] Add Waste (Auto-Detect)" << endl;
            cout << " [2] View Bins" << endl;
            cout << " [3] Process Waste (Recycle/Dispose)" << endl;
            cout << " [4] Sort Items by Weight" << endl;
            cout << " [0] Exit" << endl;
            cout << "----------------------------------------" << endl;
            cout << "Select > ";
            
            if (!(cin >> choice)) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                choice = -1; continue;
            }

            switch(choice) {
                case 1: autoDetectWasteUI(); break;
                case 2: viewBinsUI(); break;
                case 3: processWasteUI(); break;
                case 4: sortWasteUI(); break;
                case 0: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 0);
    }

    void autoDetectWasteUI() {
        string name;
        double weight;

        cout << "\n--- Smart Separation ---" << endl;
        cout << "Enter Item Name (e.g., Coke Can, Water Bottle): ";
        getline(cin >> ws, name); 

        cout << "Enter Weight (kg): ";
        if (!(cin >> weight)) { weight = 0; cin.clear(); cin.ignore(1000, '\n'); }

        string lowerName = toLower(name);
        
        if (lowerName.find("bottle") != string::npos || lowerName.find("cup") != string::npos || lowerName.find("straw") != string::npos || lowerName.find("plastic") != string::npos) {
            plasticBin->addWaste("Plastic", name, weight);
        }
        else if (lowerName.find("glass") != string::npos || lowerName.find("jar") != string::npos || lowerName.find("wine") != string::npos) {
            glassBin->addWaste("Glass", name, weight);
        }
        else if (lowerName.find("paper") != string::npos || lowerName.find("box") != string::npos || lowerName.find("book") != string::npos || lowerName.find("news") != string::npos || lowerName.find("novel") != string::npos)|| lowerName.find("magazine") != string::npos {
            paperBin->addWaste("Paper", name, weight);
        }
        else {
            cout << ">> System: Unknown Type -> Routing to General Waste (Stack)." << endl;
            generalBin->addWaste("General", name, weight);
        }
    }

    void viewBinsUI() {
        int t;
        cout << "\nSelect Bin: 1.General 2.Plastic 3.Glass 4.Paper 5.All : ";
        if (!(cin >> t)) { cin.clear(); cin.ignore(1000, '\n'); return; }
        
        if(t==1) generalBin->display();
        else if(t==2) plasticBin->display();
        else if(t==3) glassBin->display();
        else if(t==4) paperBin->display();
        else if(t==5) {
            generalBin->display(); plasticBin->display();
            glassBin->display(); paperBin->display();
        }
    }

    void processWasteUI() {
        int t;
        cout << "\nProcess Bin: 1.General 2.Plastic 3.Glass 4.Paper : ";
        if (!(cin >> t)) { cin.clear(); cin.ignore(1000, '\n'); return; }

        if(t==1) generalBin->processWaste();
        else if(t==2) plasticBin->processWaste();
        else if(t==3) glassBin->processWaste();
        else if(t==4) paperBin->processWaste();
    }

    void sortWasteUI() {
        int t;
        cout << "\nSort Bin by Weight: 1.General 2.Plastic 3.Glass 4.Paper : ";
        if (!(cin >> t)) { cin.clear(); cin.ignore(1000, '\n'); return; }

        if(t==1) generalBin->sortByWeight();
        else if(t==2) plasticBin->sortByWeight();
        else if(t==3) glassBin->sortByWeight();
        else if(t==4) paperBin->sortByWeight();
    }
};

#endif