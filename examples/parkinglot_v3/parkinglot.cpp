#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

using namespace std;

//vehicle
enum class VehicleType {
    Car,
    Bike,
    Truck
};

class Vehicle {
protected: 
    string licensePlate;
    VehicleType type;

public:
    Vehicle() : type(VehicleType::Car) {} // Default constructor
    Vehicle(string plate, VehicleType t) : licensePlate(plate), type(t) {};
    virtual ~Vehicle() {} //destructor

    //getters and setters (encapsulation)
    VehicleType getType() {
        return type;
    }

    string getPlate() { // Changed from getString to getPlate
        return licensePlate;
    }
};

//inherits publicly the vehicle class
//Everything defined in this section is publicly accessible outside the class.
//
class Car : public Vehicle {
public: // Made constructor public
    Car(string plate) : Vehicle(plate, VehicleType::Car) {}
};

class Bike : public Vehicle {
public: // Made constructor public
    Bike(string plate) : Vehicle(plate, VehicleType::Bike) {}
};

class Truck : public Vehicle {
public: // Made constructor public
    Truck(string plate) : Vehicle(plate, VehicleType::Truck) {}
};

//-------------
//parking spots

enum class SpotType {
    Compact,
    Large
};

class Ticket {
public: 
    int spotNumber;
    int entryTime;

    Ticket(int spot = 0, int entry = 0) : spotNumber(spot), entryTime(entry) {}

    int calculateFee(int exitTime) {
        int duration = exitTime - entryTime;
        int rate = 10; // 10 per hour
        return max(1, duration) * rate;
    }
};

class ParkingSpot {
protected: 
    int spotNumber;
    bool occupied;
    SpotType type;
    Vehicle* parkedVehicle; // Changed to pointer
    Ticket ticket;

public:
    ParkingSpot(int number, SpotType t) : spotNumber(number), type(t), occupied(false), parkedVehicle(nullptr) {}
    ~ParkingSpot() { delete parkedVehicle; }

    //getters and setters since they are protected
    bool isOccupied() {
        return occupied;
    }

    SpotType getType() {
        return type;
    }

    int getSpotNumber() {
        return spotNumber;
    }

    bool canFitVehicle(Vehicle& vehicle) {
        if(type == SpotType::Compact) {
            return vehicle.getType() == VehicleType::Car || vehicle.getType() == VehicleType::Bike;
        }
        return true;
    }

    bool ParkVehicle(Vehicle& vehicle, int entryTime) {
        if(occupied || !canFitVehicle(vehicle)) return false;
        
        parkedVehicle = new Vehicle(vehicle);
        ticket = Ticket(spotNumber, entryTime);
        occupied = true;
        cout << "Vehicle [" << vehicle.getPlate() << "] parked at Spot " << spotNumber << ", Entry Time: " << entryTime << endl;
        return true;
    }

    bool unpark(const string& plate, int exitTime) {
        if (!occupied || !parkedVehicle || parkedVehicle->getPlate() != plate) return false;
        int fee = ticket.calculateFee(exitTime);
        cout << "Vehicle [" << plate << "] unparked from Spot " << spotNumber
             << ". Duration: " << (exitTime - ticket.entryTime)
             << " hrs. Fee: ₹" << fee << endl;
        delete parkedVehicle;
        parkedVehicle = nullptr;
        occupied = false;
        return true;
    }

    string getParkedVehiclePlate() {
        if(occupied && parkedVehicle) return parkedVehicle->getPlate();
        return "Empty";
    }
};

//------------------
//Parkinglot - singleton

class ParkingLot {
private: 
    vector<ParkingSpot> spots;
    // It is used as part of the Singleton design pattern, where we ensure only one object of a class is ever created.
    static ParkingLot* instance;

    ParkingLot() {} //private constructor

public:
    //Prevents copying the object (e.g., ParkingLot a = b;)
    ParkingLot(const ParkingLot&) = delete;
    //Prevents assignment (e.g., a = b;)
    ParkingLot& operator=(const ParkingLot&) = delete; 

    static ParkingLot* getInstance() {
        if(!instance) {
            instance = new ParkingLot();
        }
        return instance;
    }

    void addSpot(const ParkingSpot& spot) { // Changed to const reference
        spots.push_back(spot);
    }

    bool parkVehicle(Vehicle& vehicle) {
        for(auto& spot : spots) {
            if(!spot.isOccupied() && spot.canFitVehicle(vehicle)) {
                return spot.ParkVehicle(vehicle, 0); // Using 0 as default entry time
            }
        }
        cout << "No available spot for vehicle [" << vehicle.getPlate() << "]\n";
        return false;
    }

    bool unparkVehicle(const string& plate, int exitTime) {
        for(auto& spot : spots) {
            if(spot.isOccupied() && spot.getParkedVehiclePlate() == plate) {
                return spot.unpark(plate, exitTime);
            }
        }
        cout << "Vehicle [" << plate << "] not found.\n";
        return false;
    }
};

ParkingLot* ParkingLot::instance = nullptr;

// ------------------------------------
// MAIN
// ------------------------------------

int main() {
    ParkingLot* lot = ParkingLot::getInstance();

    lot->addSpot(ParkingSpot(101, SpotType::Compact));
    lot->addSpot(ParkingSpot(102, SpotType::Large));
    lot->addSpot(ParkingSpot(103, SpotType::Compact));

    Car car1("CAR-123");
    Bike bike1("BIKE-456");
    Car car2("CAR-789");

    lot->parkVehicle(car1);   // Should park in 101
    lot->parkVehicle(bike1);  // Should park in 103 or 102
    lot->parkVehicle(car2);   // Should take remaining available spot

    return 0;
}
