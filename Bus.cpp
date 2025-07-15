#include "Bus.h"
#include "FileManager.h"

Bus::Bus() : Vehicle("", "Bus", 0), route("") {}
Bus::Bus(string id, int cap, string r) : Vehicle(id, "Bus", cap), route(r) {}

void Bus::displayDetails() {
    cout << "[Bus] ID: " << vehicleID << ", Capacity: " << capacity << ", Route: " << route << endl;
}

void Bus::inputDetails() {
    Vehicle::inputDetails();
    cout << "Enter Route: "; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, route);
}

void Bus::saveToFile(ofstream& outFile) const {
    outFile << "Type=Bus ID=" << vehicleID << " Capacity=" << capacity << " Route=" << route;
}

bool Bus::loadFromFile(stringstream& ss) {
    bool dummy = false;
    return FileManager::parseKeyValue(ss, vehicleID, capacity, route, dummy);
}