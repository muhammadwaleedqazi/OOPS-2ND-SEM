#include "Train.h"
#include <iostream>
#include "FileManager.h"
#include <sstream>

Train::Train() : Vehicle("", "Train", 0), compartments(0) {}

void Train::displayDetails() {
    cout << "[Train] ID: " << vehicleID << ", Capacity: " << capacity << ", Compartments: " << compartments << endl;
}

void Train::inputDetails() {
    Vehicle::inputDetails();
    cout << "Enter Compartments: "; 
    cin >> compartments;
}

void Train::saveToFile(ofstream& outFile) const {
    outFile << "Type=Train ID=" << vehicleID << " Capacity=" << capacity << " Compartments=" << compartments;
}

bool Train::loadFromFile(stringstream& ss) {
    string dummy;
    bool dummyBool = false;
    return FileManager::parseKeyValue(ss, vehicleID, capacity, dummy, dummyBool);
}