#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include "Vehicle.h"
#include "Booking.h"
#include "Schedule.h"
#include <string>
using namespace std;

class FileManager {
public:
    static bool saveData(Vehicle* vehicles[], int vehicleCount, Booking bookings[], int bookingCount, Schedule schedules[], int scheduleCount, const string& filename);
    static bool loadData(Vehicle* vehicles[], int& vehicleCount, Booking bookings[], int& bookingCount, Schedule schedules[], int& scheduleCount, const string& filename, int maxVehicles, int maxBookings, int maxSchedules);
    static bool parseKeyValue(stringstream& ss, string& id, int& capacity, string& extra1, bool& extra2);
};

#endif