#include "User.h"
#include "Booking.h"
#include "Schedule.h"
#include "Vehicle.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int findBooking(Booking bookings[], int bookingCount, const string& bookingID) {
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].getBookingID() == bookingID) return i;
    }
    return -1;
}

void Admin::displayMenu() {
    cout << "\n--- Admin Menu ---\n1. Add Vehicle\n2. View Vehicles\n3. Delete Vehicle\n4. Add Schedule\n5. View Schedules\n6. View All Bookings\n7. Modify Booking\n8. View Vehicle Availability\n9. Exit\n";
}

void Admin::viewBookings(Booking bookings[], int bookingCount) {
    if (bookingCount == 0) {
        cout << "No bookings available.\n";
        return;
    }
    cout << "\n--- All Bookings ---\n" << left << setw(10) << "Booking ID" << setw(20) << "Passenger" 
              << setw(12) << "Vehicle ID" << setw(12) << "Date" << setw(8) << "Seats" << "\n" << string(62, '-') << "\n";
    for (int i = 0; i < bookingCount; i++) bookings[i].displayBooking();
}

void Admin::modifyBooking(Booking bookings[], int& bookingCount, Schedule schedules[], int scheduleCount, Vehicle* vehicles[], int vehicleCount, const string& filename) {
    if (bookingCount == 0) {
        cout << "No bookings available to modify.\n";
        return;
    }
    viewBookings(bookings, bookingCount);
    cout << "Enter Booking ID to modify: ";
    string bookingID;
    getline(cin, bookingID);
    int index = findBooking(bookings, bookingCount, bookingID);
    if (index == -1) {
        cout << "Error: Booking ID not found.\n";
        return;
    }
    cout << "Enter new Number of Seats: ";
    int seats;
    while (!(cin >> seats) || seats <= 0) {
        cout << "Invalid seats. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter new Date: ";
    string date;
    getline(cin, date);
    bookings[index] = Booking(bookings[index].getBookingID(), bookings[index].getPassengerName(), 
                             bookings[index].getVehicleID(), date, seats);
    FileManager::saveData(vehicles, vehicleCount, bookings, bookingCount, schedules, scheduleCount, filename);
    cout << "Booking modified successfully!\n";
}

void Admin::viewVehicleAvailability(Vehicle* vehicles[], int vehicleCount, Booking bookings[], int bookingCount, Schedule schedules[], int scheduleCount) {
    if (vehicleCount == 0 || scheduleCount == 0) {
        cout << "No vehicles or schedules available.\n";
        return;
    }
    cout << "Enter Vehicle ID: ";
    string vehicleID;
    getline(cin, vehicleID);
    cout << "Enter Date: ";
    string date;
    getline(cin, date);
    int capacity = 0;
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i]->getVehicleID() == vehicleID) {
            capacity = vehicles[i]->getCapacity();
            break;
        }
    }
    if (capacity == 0) {
        cout << "Error: Vehicle ID not found.\n";
        return;
    }
    int bookedSeats = 0;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].getVehicleID() == vehicleID && bookings[i].getDate() == date) {
            bookedSeats += bookings[i].getSeats();
        }
    }
    cout << "Vehicle " << vehicleID << " on " << date << ": " 
              << (capacity - bookedSeats) << " seats available (Total: " << capacity << ", Booked: " << bookedSeats << ")\n";
}

void Passenger::displayMenu() {
    cout << "\n--- Passenger Menu ---\n1. Book Ride\n2. View My Bookings\n3. Cancel Booking\n4. View All Bookings\n5. Exit\n";
}

void Passenger::viewMyBookings(Booking bookings[], int bookingCount, const string& passengerName) {
    bool found = false;
    cout << "\n--- Your Bookings ---\n";
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].getPassengerName() == passengerName) {
            bookings[i].displayBooking();
            found = true;
        }
    }
    if (!found) cout << "No bookings found for " << passengerName << ".\n";
}

void Passenger::cancelBooking(Booking bookings[], int& bookingCount, const string& passengerName, const string& filename) {
    if (bookingCount == 0) {
        cout << "No bookings available.\n";
        return;
    }
    viewMyBookings(bookings, bookingCount, passengerName);
    cout << "Enter Booking ID to cancel: ";
    string bookingID;
    getline(cin, bookingID);
    int index = -1;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].getBookingID() == bookingID && bookings[i].getPassengerName() == passengerName) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Error: Booking ID not found or not yours.\n";
        return;
    }
    for (int i = index; i < bookingCount - 1; i++) bookings[i] = bookings[i + 1];
    bookingCount--;
    FileManager::saveData(nullptr, 0, bookings, bookingCount, nullptr, 0, filename);
    cout << "Booking cancelled successfully!\n";
}