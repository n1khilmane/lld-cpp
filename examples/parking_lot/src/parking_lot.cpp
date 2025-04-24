#include "parking_lot.h"
#include <iostream>

Vehicle::Vehicle(VehicleType type, const std::string& licensePlate)
    : type(type), licensePlate(licensePlate) {}

VehicleType Vehicle::getType() const {
    return type;
}

const std::string& Vehicle::getLicensePlate() const {
    return licensePlate;
}

ParkingSpot::ParkingSpot(int id, VehicleType type)
    : id(id), type(type), vehicle(nullptr) {}

bool ParkingSpot::isOccupied() const {
    return vehicle != nullptr;
}

void ParkingSpot::parkVehicle(std::shared_ptr<Vehicle> vehicle) {
    this->vehicle = vehicle;
}

void ParkingSpot::removeVehicle() {
    vehicle = nullptr;
}

int ParkingSpot::getId() const {
    return id;
}

VehicleType ParkingSpot::getType() const {
    return type;
}

ParkingLot::ParkingLot(int numSpots) {
    for (int i = 0; i < numSpots; ++i) {
        // Alternate between different vehicle types
        VehicleType type = static_cast<VehicleType>(i % 3);
        spots.emplace_back(i + 1, type);
    }
}

bool ParkingLot::parkVehicle(std::shared_ptr<Vehicle> vehicle) {
    for (auto& spot : spots) {
        if (!spot.isOccupied() && spot.getType() == vehicle->getType()) {
            spot.parkVehicle(vehicle);
            return true;
        }
    }
    return false;
}

bool ParkingLot::removeVehicle(const std::string& licensePlate) {
    for (auto& spot : spots) {
        if (spot.isOccupied() && 
            spot.getVehicle()->getLicensePlate() == licensePlate) {
            spot.removeVehicle();
            return true;
        }
    }
    return false;
}

void ParkingLot::displayStatus() const {
    std::cout << "Parking Lot Status:\n";
    for (const auto& spot : spots) {
        std::cout << "Spot " << spot.getId() << ": ";
        if (spot.isOccupied()) {
            std::cout << "Occupied by " << spot.getVehicle()->getLicensePlate();
        } else {
            std::cout << "Empty";
        }
        std::cout << "\n";
    }
} 