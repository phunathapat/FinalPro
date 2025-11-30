#ifndef WASTELIST_H
#define WASTELIST_H

#include <iostream>
#include <iomanip>
#include "WasteNode.h"

using namespace std;

class WasteList {
private:
    WasteNode* head;
    WasteNode* tail;
    string categoryName;
    bool isStackMode; 

public:
    WasteList(string name, bool stackMode = false) {
        head = nullptr;
        tail = nullptr;
        categoryName = name;
        isStackMode = stackMode;
    }

    ~WasteList() {
        while (head != nullptr) {
            WasteNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addWaste(string type, string name, double w) {
        WasteNode* newNode = new WasteNode(type, name, w);

        if (isStackMode) {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) tail = newNode; 
            cout << ">> [Stack Push] Threw " << name << " on TOP of " << categoryName << " bin." << endl;
        } else {
            if (head == nullptr) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            cout << ">> [Queue Add] Added " << name << " to " << categoryName << " line." << endl;
        }
    }

    void processWaste() {
        if (head == nullptr) {
            cout << ">> [" << categoryName << "] is empty." << endl;
            return;
        }

        WasteNode* temp = head;
        cout << "\n>>> PROCESSING (" << (isStackMode ? "Stack Pop" : "Queue Dequeue") << ") <<<" << endl;
        cout << "Item: " << temp->getName() << " | Weight: " << temp->getWeight() << " kg -> [PROCESSED]" << endl;

        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;

        display();
    }

    void sortByWeight() {
        if (head == nullptr || head->next == nullptr) {
            cout << ">> Not enough items to sort." << endl;
            return;
        }

        bool swapped;
        do {
            swapped = false;
            WasteNode* current = head;
            while (current->next != nullptr) {
                if (current->getWeight() < current->next->getWeight()) {
                    string tType = current->getType();
                    string tName = current->getName();
                    double tWeight = current->getWeight();

                    current->setType(current->next->getType());
                    current->setName(current->next->getName());
                    current->setWeight(current->next->getWeight());

                    current->next->setType(tType);
                    current->next->setName(tName);
                    current->next->setWeight(tWeight);

                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << ">> [Sorted] " << categoryName << " sorted by weight (Heavy -> Light)." << endl;
        display();
    }

    void display() {
        cout << "\n .------------------------------------------." << endl;
        cout << " | BIN STATUS: " << left << setw(28) << categoryName << " |" << endl;
        cout << " | Mode: " << setw(34) << (isStackMode ? "STACK (Top-Down)" : "QUEUE (First-In)") << " |" << endl;
        cout << " |------------------------------------------|" << endl;
        
        if (head == nullptr) {
            cout << " |              ( Empty )                   |" << endl;
            cout << " '------------------------------------------'" << endl;
            return;
        }

        WasteNode* current = head;
        int i = 1;
        double totalW = 0;
        
        cout << " | " << left << setw(4) << "No." << setw(20) << "Item Name" << setw(13) << "Weight (kg)" << "|" << endl;
        cout << " |------------------------------------------|" << endl;
        while (current != nullptr) {
            totalW += current->getWeight();
            cout << " | " << left << setw(4) << i++ 
                 << setw(20) << current->getName() 
                 << fixed << setprecision(2) << setw(10) << current->getWeight() << " kg |" << endl;
            current = current->next;
        }
        cout << " |------------------------------------------|" << endl;
        cout << " | TOTAL: " << setw(5) << (i-1) << " items | SUM: " << setw(8) << totalW << " kg |" << endl;
        cout << " '------------------------------------------'" << endl;
    }
};

#endif