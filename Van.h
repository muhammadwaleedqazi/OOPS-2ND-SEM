#ifndef VAN_H
#define VAN_H
#include "Vehicle.h"
#include <sstream>
using namespace std;

class Van : public Vehicle {
    bool isAC;

public:
    Van();
    Van(string id, int cap, bool ac);
    void displayDetails() override;
    void inputDetails() override;
    void saveToFile(ofstream& outFile) const override;
    bool loadFromFile(stringstream& ss) override;
};

#endif