#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Schedule {
    string vehicleID;
    string route;
    string departureTime;
    string date;

public:
    Schedule();
    Schedule(string id, string r, string dt, string d = "");
    void displaySchedule();
    void saveToFile(ofstream& outFile) const;
    bool loadFromFile(stringstream& ss);
    string getVehicleID() const { return vehicleID; }
    string getDate() const { return date; }
    string getRoute() const { return route; }
};

#endif