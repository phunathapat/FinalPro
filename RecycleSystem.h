#ifndef RECYCLESYSTEM_H
#define RECYCLESYSTEM_H

#include <iostream>
#include <limits> 
#include "WasteQueue.h"

using namespace std;

class RecycleSystem {
private:
    WasteQueue* generalQ;
    WasteQueue* plasticQ;
    WasteQueue* glassQ;
    WasteQueue* paperQ;

public:
    RecycleSystem() {
        generalQ = new WasteQueue("General Waste");
        plasticQ = new WasteQueue("Plastic");
        glassQ   = new WasteQueue("Glass");
        paperQ   = new WasteQueue("Paper");
    }

    ~RecycleSystem() {
        delete generalQ;
        delete plasticQ;
        delete glassQ;
        delete paperQ;
        cout << "[System] Recycle System Shutdown Complete." << endl;
    }

    void run() {
        int choice;
        do {
            cout << "\n============================" << endl;
            cout << "    RECYCLE CENTER SYSTEM    " << endl;
            cout << "============================" << endl;
            cout << "1. Add Waste (Separation)" << endl;
            cout << "2. Print Queue" << endl;
            cout << "3. Process (Dequeue)" << endl;
            cout << "0. Exit" << endl;
            cout << "Select: ";
            
            if (!(cin >> choice)) {
                cout << ">>> Error: Please enter a NUMBER." << endl;
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                choice = -1; 
                continue;
            }

            switch(choice) {
                case 1: addWasteUI(); break;
                case 2: printQueueUI(); break;
                case 3: processWasteUI(); break;
                case 0: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 0);
    }

    void addWasteUI() {
        int type;
        string name;
        double weight;

        cout << "\n[Step 1] Select Type:" << endl;
        cout << "1.General | 2.Plastic | 3.Glass | 4.Paper : ";
        while(!(cin >> type)) { 
            cout << "Invalid! Enter number 1-4: ";
            cin.clear(); cin.ignore(1000, '\n');
        }

        cout << "[Step 2] Enter Waste Name: ";
        getline(cin >> ws, name); 

        cout << "[Step 3] Enter Weight (kg): ";
        if (!(cin >> weight)) { 
            cout << ">>> Error: Invalid weight! Defaulting to 0." << endl;
            cin.clear(); cin.ignore(1000, '\n');
            weight = 0;
        }

        switch (type) {
            case 1: generalQ->enqueue("General", name, weight); break;
            case 2: plasticQ->enqueue("Plastic", name, weight); break;
            case 3: glassQ->enqueue("Glass", name, weight); break;
            case 4: paperQ->enqueue("Paper", name, weight); break;
            default: cout << "Invalid Type! Cancelled." << endl;
        }
    }

    void printQueueUI() {
        int type;
        cout << "\n-----------------------------------" << endl;
        cout << "View Queue Option:" << endl;
        cout << "1. General Waste" << endl;
        cout << "2. Plastic" << endl;
        cout << "3. Glass" << endl;
        cout << "4. Paper" << endl;
        cout << "5. [SHOW ALL QUEUES]" << endl; 
        cout << "Select (1-5): ";
        
        if (!(cin >> type)) { 
            cin.clear(); cin.ignore(1000, '\n'); 
            cout << "Invalid Input" << endl; return;
        }

        switch (type) {
            case 1: generalQ->display(); break;
            case 2: plasticQ->display(); break;
            case 3: glassQ->display(); break;
            case 4: paperQ->display(); break;
            case 5: 
                cout << "\n>>> DISPLAYING ALL CATEGORIES <<<" << endl;
                generalQ->display();
                plasticQ->display();
                glassQ->display();
                paperQ->display();
                break;
            default: cout << "Invalid Selection" << endl;
        }
    }

    void processWasteUI() {
        int type;
        cout << "\nProcess Queue: 1.General | 2.Plastic | 3.Glass | 4.Paper : ";
        if (!(cin >> type)) {
            cin.clear(); cin.ignore(1000, '\n'); 
            cout << "Invalid Input" << endl; return;
        }
        switch (type) {
            case 1: generalQ->dequeue(); break;
            case 2: plasticQ->dequeue(); break;
            case 3: glassQ->dequeue(); break;
            case 4: paperQ->dequeue(); break;
            default: cout << "Invalid Selection" << endl;
        }
    }
};

#endif