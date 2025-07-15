#include "Vehicle.h"
#include "FileManager.h"
#include <limits>

void Vehicle::inputDetails() {
    cout << "Enter Vehicle ID: ";
    cin >> vehicleID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    cout << "Enter Capacity: ";
    while (!(cin >> capacity) || capacity <= 0) {
        cout << "Invalid capacity. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}