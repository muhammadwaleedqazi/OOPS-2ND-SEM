#ifndef BOOKING_H
#define BOOKING_H
#include <string>
#include <fstream>
using namespace std;

class Booking {
private:
    string bookingID;
    string passengerName;
    string vehicleID;
    string date;
    int seats;

public:
    Booking() : bookingID(""), passengerName(""), vehicleID(""), date(""), seats(0) {}
    Booking(string bID, string name, string vID, string d, int s)
        : bookingID(bID), passengerName(name), vehicleID(vID), date(d), seats(s) {}
    void displayBooking() const;
    void saveToFile(ofstream& outFile) const;
    bool loadFromFile(stringstream& ss);
    string getVehicleID() const { return vehicleID; }
    string getBookingID() const { return bookingID; }
    string getPassengerName() const { return passengerName; }
    string getDate() const { return date; }
    int getSeats() const { return seats; }
};

#endif