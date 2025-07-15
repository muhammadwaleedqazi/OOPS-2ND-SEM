#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Bus.h"
#include "Train.h"
#include "Van.h"
#include "Booking.h"
#include "User.h"
#include "Schedule.h"
#include "FileManager.h"
using namespace std;

const int MAX_VEHICLES = 100;
const int MAX_BOOKINGS = 100;
const int MAX_SCHEDULES = 100;

bool vehicleExists(Vehicle* vehicles[], int vehicleCount, const string& vehicleID) {
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i] && vehicles[i]->getVehicleID() == vehicleID) return true;
    }
    return false;
}

int main() {
    Vehicle* vehicles[MAX_VEHICLES] = {nullptr};
    Booking bookings[MAX_BOOKINGS];
    Schedule schedules[MAX_SCHEDULES];
    int vehicleCount = 0, bookingCount = 0, scheduleCount = 0;
    int choice;

    FileManager::loadData(vehicles, vehicleCount, bookings, bookingCount, schedules, scheduleCount, "travel_data.txt", MAX_VEHICLES, MAX_BOOKINGS, MAX_SCHEDULES);

    do {
        cout << "\n--- Main Menu ---\n1. Admin\n2. Passenger\n0. Exit\nEnter choice: ";
        while (!(cin >> choice) || choice < 0 || choice > 2) {
            cout << "Invalid choice. Enter 0, 1, or 2: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            Admin admin("AdminUser");
            int aChoice;
            do {
                admin.displayMenu();
                while (!(cin >> aChoice) || aChoice < 1 || aChoice > 9) {
                    cout << "Invalid choice. Enter 1-8: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (aChoice == 1) {
                    if (vehicleCount >= MAX_VEHICLES) {
                        cout << "Cannot add more vehicles. Maximum limit reached.\n";
                        continue;
                    }
                    cout << "\nEnter Vehicle Type (1=Bus, 2=Train, 3=Van): ";
                    int vType;
                    while (!(cin >> vType) || vType < 1 || vType > 3) {
                        cout << "Invalid type. Enter 1, 2, or 3: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    Vehicle* v = nullptr;
                    if (vType == 1) v = new Bus();
                    else if (vType == 2) v = new Train();
                    else v = new Van();
                    v->inputDetails();
                    if (vehicleExists(vehicles, vehicleCount, v->getVehicleID())) {
                        cout << "Error: Vehicle ID '" << v->getVehicleID() << "' already exists.\n";
                        delete v;
                        continue;
                    }
                    vehicles[vehicleCount++] = v;
                    cout << "Vehicle added successfully!\n";
                } else if (aChoice == 2) {
                    for (int i = 0; i < vehicleCount; i++) vehicles[i]->displayDetails();
                } else if (aChoice == 3) {
                    cout << "Available Vehicle IDs: ";
                    for (int i = 0; i < vehicleCount; i++) {
                        cout << vehicles[i]->getVehicleID() << (i < vehicleCount - 1 ? ", " : "\n");
                    }
                    cout << "Enter Vehicle ID to delete: ";
                    string vehicleID;
                    getline(cin, vehicleID);
                    int index = -1;
                    for (int i = 0; i < vehicleCount; i++) {
                        if (vehicles[i] && vehicles[i]->getVehicleID() == vehicleID) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        cout << "Error: Vehicle ID not found.\n";
                        continue;
                    }
                    char confirm;
                    cout << "Are you sure you want to delete vehicle " << vehicleID << "? (y/n): ";
                    cin >> confirm;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (confirm != 'y' && confirm != 'Y') {
                        cout << "Deletion cancelled.\n";
                        continue;
                    }
                    int newCount = 0;
                    for (int i = 0; i < scheduleCount; i++) {
                        if (schedules[i].getVehicleID() != vehicleID) schedules[newCount++] = schedules[i];
                    }
                    scheduleCount = newCount;
                    newCount = 0;
                    for (int i = 0; i < bookingCount; i++) {
                        if (bookings[i].getVehicleID() != vehicleID) bookings[newCount++] = bookings[i];
                    }
                    bookingCount = newCount;
                    delete vehicles[index];
                    for (int i = index; i < vehicleCount - 1; i++) vehicles[i] = vehicles[i + 1];
                    vehicles[--vehicleCount] = nullptr;
                    cout << "Vehicle and associated schedules/bookings deleted successfully!\n";
                } else if (aChoice == 4) {
                    if (scheduleCount >= MAX_SCHEDULES) {
                        cout << "Cannot add more schedules. Maximum limit reached.\n";
                        continue;
                    }
                    cout << "Available Vehicle IDs: ";
                    for (int i = 0; i < vehicleCount; i++) {
                        cout << vehicles[i]->getVehicleID() << (i < vehicleCount - 1 ? ", " : "\n");
                    }
                    cout << "Enter Vehicle ID: ";
                    string vehicleID;
                    getline(cin, vehicleID);
                    if (!vehicleExists(vehicles, vehicleCount, vehicleID)) {
                        cout << "Error: Vehicle ID not found.\n";
                        continue;
                    }
                    cout << "Enter Route: ";
                    string route;
                    getline(cin, route);
                    string departureTime, date;
                    cout << "Enter Departure Time: ";
                    getline(cin, departureTime);
                    departureTime.erase(departureTime.begin(), find_if(departureTime.begin(), departureTime.end(), [](char c) { return !isspace(c); }));
                    departureTime.erase(find_if(departureTime.rbegin(), departureTime.rend(), [](char c) { return !isspace(c); }).base(), departureTime.end());
                    if (departureTime.empty()) {
                        cout << "Error: Departure time cannot be empty.\n";
                        continue;
                    }
                    cout << "Enter Date: ";
                    getline(cin, date);
                    date.erase(date.begin(), find_if(date.begin(), date.end(), [](char c) { return !isspace(c); }));
                    date.erase(find_if(date.rbegin(), date.rend(), [](char c) { return !isspace(c); }).base(), date.end());
                    if (date.empty()) {
                        cout << "Error: Date cannot be empty.\n";
                        continue;
                    }
                    schedules[scheduleCount++] = Schedule(vehicleID, route, departureTime, date);
                    cout << "Schedule added successfully!\n";
                } else if (aChoice == 5) {
                    for (int i = 0; i < scheduleCount; i++) schedules[i].displaySchedule();
                } else if (aChoice == 6) {
                    admin.viewBookings(bookings, bookingCount);
                } else if (aChoice == 7) {
                    admin.modifyBooking(bookings, bookingCount, schedules, scheduleCount, vehicles, vehicleCount, "travel_data.txt");
                } else if (aChoice == 8) {
                    admin.viewVehicleAvailability(vehicles, vehicleCount, bookings, bookingCount, schedules, scheduleCount);
                }
            } while (aChoice != 9);
        } else if (choice == 2) {
            Passenger passenger("PassengerUser");
            int pChoice;
            do {
                passenger.displayMenu();
                while (!(cin >> pChoice) || pChoice < 1 || pChoice > 5) {
                    cout << "Invalid choice. Enter 1-5: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (pChoice == 1) {
                    if (bookingCount >= MAX_BOOKINGS) {
                        cout << "Cannot add more bookings. Maximum limit reached.\n";
                        continue;
                    }
                    cout << "\nAvailable Schedules:\n";
                    if (scheduleCount == 0) {
                        cout << "No schedules available.\n";
                        continue;
                    }
                    for (int i = 0; i < scheduleCount; i++) {
                        cout << i + 1 << ". ";
                        schedules[i].displaySchedule();
                    }
                    int scheduleIndex;
                    cout << "Select schedule number: ";
                    while (!(cin >> scheduleIndex) || scheduleIndex < 1 || scheduleIndex > scheduleCount) {
                        cout << "Invalid schedule number. Enter 1-" << scheduleCount << ": ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    scheduleIndex--;
                    string name, vehicleID, date;
                    int seats;
                    cout << "Enter Name: ";
                    getline(cin, name);
                    vehicleID = schedules[scheduleIndex].getVehicleID();
                    date = schedules[scheduleIndex].getDate();
                    cout << "Enter Number of Seats: ";
                    while (!(cin >> seats) || seats <= 0) {
                        cout << "Invalid seats. Enter a positive number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    bookings[bookingCount] = Booking("B" + to_string(bookingCount + 1), name, vehicleID, date, seats);
                    bookingCount++;
                    cout << "Booking Successful!\n";
                } else if (pChoice == 2) {
                    cout << "Enter your name: ";
                    string name;
                    getline(cin, name);
                    passenger.viewMyBookings(bookings, bookingCount, name);
                } else if (pChoice == 3) {
                    cout << "Enter your name: ";
                    string name;
                    getline(cin, name);
                    passenger.cancelBooking(bookings, bookingCount, name, "travel_data.txt");
                } else if (pChoice == 4) {
                    for (int i = 0; i < bookingCount; i++) bookings[i].displayBooking();
                }
            } while (pChoice != 5);
        }
    } while (choice != 0);

    FileManager::saveData(vehicles, vehicleCount, bookings, bookingCount, schedules, scheduleCount, "travel_data.txt");
    for (int i = 0; i < vehicleCount; i++) delete vehicles[i];

    return 0;
}