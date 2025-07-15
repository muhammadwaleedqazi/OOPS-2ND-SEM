#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std; 

class Vehicle {
protected:
    string vehicleID; 
    string type;      
    int capacity;

public:
    Vehicle() : vehicleID(""), type(""), capacity(0) {}
    Vehicle(string id, string t, int cap) : vehicleID(id), type(t), capacity(cap) {}  

    virtual void displayDetails() = 0;
    virtual void inputDetails();
    virtual void saveToFile(ofstream& outFile) const = 0; 
    virtual bool loadFromFile(stringstream& ss) = 0;     

    string getVehicleID() const { return vehicleID; } 
    string getType() const { return type; }           
    int getCapacity() const { return capacity; }
    virtual ~Vehicle() {}
};

#endif