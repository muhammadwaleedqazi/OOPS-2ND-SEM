#ifndef BUS_H
#define BUS_H
#include "Vehicle.h"
#include <sstream>
#include<limits>
using namespace std;

class Bus : public Vehicle {
    string route;

public:
    Bus();
    Bus(string id, int cap, string r);
    void displayDetails() override;
    void inputDetails() override;
    void saveToFile(ofstream& outFile) const override;
    bool loadFromFile(stringstream& ss) override;
};

#endif