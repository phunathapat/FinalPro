#ifndef WASTENODE_H
#define WASTENODE_H

#include <iostream>
#include <string>
using namespace std;

class WasteNode {
private:
    string wasteType;
    string wasteName;
    double weight;

public:
    WasteNode* next;

    WasteNode(string type, string name, double w) {
        wasteType = type;
        wasteName = name;
        weight = w;
        next = NULL;
    }

    ~WasteNode() { }

    string getType()   { return wasteType; }
    string getName()   { return wasteName; }
    double getWeight() { return weight; }

    void setType(string t)   { wasteType = t; }
    void setName(string n)   { wasteName = n; }
    void setWeight(double w) { weight = w; }
}; 
#endif