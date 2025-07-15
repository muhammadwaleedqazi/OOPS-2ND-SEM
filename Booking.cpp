#include "Booking.h"
#include <iostream>
#include <sstream>

void Booking::displayBooking() const {
    cout << "Booking ID: " << bookingID << ", Passenger: " << passengerName
         << ", Vehicle ID: " << vehicleID << ", Date: " << date
         << ", Seats: " << seats << "\n";
}

void Booking::saveToFile(ofstream& outFile) const {
    outFile << bookingID << ",\"" << passengerName << "\"," << vehicleID << "," << date << "," << seats;
}

bool Booking::loadFromFile(stringstream& ss) {
    string line;
    if (!getline(ss, line)) return false;
    stringstream lineStream(line);
    if (!getline(lineStream, bookingID, ',')) return false;
    if (lineStream.peek() == '"') {
        lineStream.get();
        if (!getline(lineStream, passengerName, '"')) return false;
        lineStream.ignore(1, ',');
    } else return false;
    if (!getline(lineStream, vehicleID, ',')) return false;
    if (!getline(lineStream, date, ',')) return false;
    string temp;
    if (!getline(lineStream, temp)) return false;
    seats = stoi(temp);
    return true;
}