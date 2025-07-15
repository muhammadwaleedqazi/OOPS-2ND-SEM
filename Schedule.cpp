#include "Schedule.h"
#include <iostream>

Schedule::Schedule() : vehicleID(""), route(""), departureTime(""), date("") {}

Schedule::Schedule(string id, string r, string dt, string d) : vehicleID(id), route(r), departureTime(dt), date(d) {}

void Schedule::displaySchedule() {
    cout << "Vehicle ID: " << vehicleID << ", Route: " << route << ", Departure: " << departureTime << ", Date: " << date << endl;
}

void Schedule::saveToFile(ofstream& outFile) const {
    outFile << "VehicleID=" << vehicleID << " Route=" << route << " DepartureTime=" << departureTime << " Date=" << date;
}

bool Schedule::loadFromFile(stringstream& ss) {
    string key;
    vehicleID.clear();
    route.clear();
    departureTime.clear();
    date.clear();
    while (ss >> key) {
        if (key.substr(0, 10) == "VehicleID=") vehicleID = key.substr(10);
        else if (key.substr(0, 6) == "Route=") route = key.substr(6);
        else if (key.substr(0, 14) == "DepartureTime=") departureTime = key.substr(14);
        else if (key.substr(0, 5) == "Date=") date = key.substr(5);
    }
    return !vehicleID.empty();
}