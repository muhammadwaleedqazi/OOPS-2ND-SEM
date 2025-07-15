#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;

class Booking;
class Schedule;
class Vehicle; 

class User {
protected:
    string username;

public:
    virtual void displayMenu() = 0;
    virtual ~User() {}
};

class Admin : public User {
public:
    Admin(string name) { username = name; }
    void displayMenu() override;
    void viewBookings(Booking bookings[], int bookingCount);
    void modifyBooking(Booking bookings[], int& bookingCount, Schedule schedules[], int scheduleCount, Vehicle* vehicles[], int vehicleCount, const string& filename);
    void viewVehicleAvailability(Vehicle* vehicles[], int vehicleCount, Booking bookings[], int bookingCount, Schedule schedules[], int scheduleCount);
};

class Passenger : public User {
public:
    Passenger(string name) { username = name; }
    void displayMenu() override;
    void viewMyBookings(Booking bookings[], int bookingCount, const string& passengerName);
    void cancelBooking(Booking bookings[], int& bookingCount, const string& passengerName, const string& filename);
};

#endif