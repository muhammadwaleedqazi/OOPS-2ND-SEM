#ifndef TRAIN_H
#define TRAIN_H
#include "Vehicle.h"
#include <sstream>
using namespace std;

class Train : public Vehicle {
    int compartments;

public:
    Train();
    Train(string id, int cap, int comp);
    void displayDetails() override;
    void inputDetails() override;
    void saveToFile(ofstream& outFile) const override;
    bool loadFromFile(stringstream& ss) override;
};

#endif