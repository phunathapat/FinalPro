#ifndef WASTEQUEUE_H
#define WASTEQUEUE_H

#include <iostream>
#include <iomanip>
#include "WasteNode.h" 

using namespace std;

class WasteQueue {
private:
    WasteNode* head;
    WasteNode* tail;
    string queueName; 

public:
    WasteQueue(string name) {
        head = nullptr;
        tail = nullptr;
        queueName = name;
    }

    ~WasteQueue() {
        cout << "[System] Cleaning queue: " << queueName << "..." << endl;
        while (head != nullptr) {
            WasteNode* temp = head;
            head = head->next;
            delete temp; 
        }
    }

    void enqueue(string type, string name, double w) {
        WasteNode* newNode = new WasteNode(type, name, w);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << ">> Added [" << name << "] to " << queueName << " Queue." << endl;
    }

    void dequeue() {
        if (head == nullptr) {
            cout << ">> [" << queueName << "] is empty. Nothing to process." << endl;
            return;
        }

        WasteNode* temp = head;
        cout << "\n>>> PROCESSING WASTE <<<" << endl;
        cout << "Type: " << temp->getType() << " | Name: " << temp->getName() 
             << " | Weight: " << temp->getWeight() << " kg -> [RECYCLED]" << endl;

        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp; 

        display();
    }

    void display() {
        cout << "\n========================================" << endl;
        cout << "   QUEUE STATUS: " << queueName << endl;
        cout << "========================================" << endl;

        if (head == nullptr) {
            cout << "(Empty Queue)" << endl;
            cout << "========================================" << endl;
            return;
        }

        WasteNode* current = head;
        int count = 0;
        double totalWeight = 0.0; 

        cout << left << setw(5) << "No." << setw(20) << "Name" << setw(10) << "Weight" << endl;
        cout << "----------------------------------------" << endl;
        
        while (current != nullptr) {
            count++;
            totalWeight += current->getWeight(); 

            cout << left << setw(5) << count
                 << setw(20) << current->getName() 
                 << setw(10) << current->getWeight() << " kg" << endl;
            
            current = current->next;
        }
        cout << "----------------------------------------" << endl;
        cout << ">> Total Items : " << count << " items" << endl;
        cout << ">> Total Weight: " << totalWeight << " kg" << endl;
        cout << "========================================" << endl;
    }
};

#endif