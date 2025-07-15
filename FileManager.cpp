#include "FileManager.h"
#include "Bus.h"
#include "Train.h"
#include "Van.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool FileManager::parseKeyValue(stringstream& ss, string& id, int& capacity, string& extra1, bool& extra2) {
    string key;
    id.clear();
    capacity = 0;
    extra1.clear();
    extra2 = false;
    while (ss >> key) {
        if (key.substr(0, 3) == "ID=") id = key.substr(3);
        else if (key.substr(0, 9) == "Capacity=") capacity = stoi(key.substr(9));
        else if (key.substr(0, 6) == "Route=") extra1 = key.substr(6);
        else if (key.substr(0, 12) == "Compartments=") capacity = stoi(key.substr(12));
        else if (key.substr(0, 3) == "AC=") extra2 = (key.substr(3) == "Yes");
    }
    return !id.empty();
}

bool FileManager::saveData(Vehicle* vehicles[], int vehicleCount, Booking bookings[], int bookingCount, Schedule schedules[], int scheduleCount, const string& filename) {
    ofstream outFile(filename, ios::out | ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error: Could not open file " << filename << " for writing.\n";
        return false;
    }
    outFile << "[VEHICLES]\n";
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i]) {
            vehicles[i]->saveToFile(outFile);
            outFile << "\n";
        }
    }
    outFile << "[BOOKINGS]\n";
    for (int i = 0; i < bookingCount; i++) {
        bookings[i].saveToFile(outFile);
        outFile << "\n";
    }
    outFile << "[SCHEDULES]\n";
    for (int i = 0; i < scheduleCount; i++) {
        schedules[i].saveToFile(outFile);
        outFile << "\n";
    }
    outFile.close();
    return true;
}

bool FileManager::loadData(Vehicle* vehicles[], int& vehicleCount, Booking bookings[], int& bookingCount, Schedule schedules[], int& scheduleCount, const string& filename, int maxVehicles, int maxBookings, int maxSchedules) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Warning: Could not open file " << filename << " for reading.\n";
        return false;
    }
    vehicleCount = bookingCount = scheduleCount = 0;
    string line;
    enum class Section { None, Vehicles, Bookings, Schedules } currentSection = Section::None;

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        if (line == "[VEHICLES]") { currentSection = Section::Vehicles; continue; }
        if (line == "[BOOKINGS]") { currentSection = Section::Bookings; continue; }
        if (line == "[SCHEDULES]") { currentSection = Section::Schedules; continue; }

        stringstream ss(line);
        if (currentSection == Section::Vehicles && vehicleCount < maxVehicles) {
            string type;
            if (!getline(ss, type, ' ') || type.substr(0, 5) != "Type=") continue;
            type = type.substr(5);
            Vehicle* vehicle = nullptr;
            if (type == "Bus") vehicle = new Bus();
            else if (type == "Train") vehicle = new Train();
            else if (type == "Van") vehicle = new Van();
            else continue;
            if (vehicle && vehicle->loadFromFile(ss)) {
                bool duplicate = false;
                for (int i = 0; i < vehicleCount; i++) {
                    if (vehicles[i]->getVehicleID() == vehicle->getVehicleID()) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) vehicles[vehicleCount++] = vehicle;
                else delete vehicle;
            } else delete vehicle;
        } else if (currentSection == Section::Bookings && bookingCount < maxBookings) {
            Booking booking;
            if (booking.loadFromFile(ss)) bookings[bookingCount++] = booking;
        } else if (currentSection == Section::Schedules && scheduleCount < maxSchedules) {
            Schedule schedule;
            if (schedule.loadFromFile(ss)) schedules[scheduleCount++] = schedule;
        }
    }
    inFile.close();
    return true;
}