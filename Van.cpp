#include "Van.h"
#include "FileManager.h"
#include <iostream>

Van::Van() : Vehicle("", "Van", 0), isAC(false) {}

void Van::displayDetails() {
    cout << "[Van] ID: " << vehicleID << ", Capacity: " << capacity << ", AC: " << (isAC ? "Yes" : "No") << endl;
}

void Van::inputDetails() {
    Vehicle::inputDetails();
    char ch;
    cout << "Is it AC (y/n)? "; 
    cin >> ch;
    isAC = (ch == 'y' || ch == 'Y');
}

void Van::saveToFile(ofstream& outFile) const {
    outFile << "Type=Van ID=" << vehicleID << " Capacity=" << capacity << " AC=" << (isAC ? "Yes" : "No");
}

bool Van::loadFromFile(stringstream& ss) {
    string dummy;
    return FileManager::parseKeyValue(ss, vehicleID, capacity, dummy, isAC);
}