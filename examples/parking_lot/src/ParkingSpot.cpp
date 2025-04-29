#include "../include/ParkingSpot.hpp"

ParkingSpot::ParkingSpot(int number, VehicleType type)
    : spotNumber(number), spotType(type), isOccupied(false), parkedVehicle(nullptr) {}

int ParkingSpot::getSpotNumber() const {
    return spotNumber;
}

VehicleType ParkingSpot::getSpotType() const {
    return spotType;
}

bool ParkingSpot::getIsOccupied() const {
    return isOccupied;
}

std::shared_ptr<Vehicle> ParkingSpot::getParkedVehicle() const {
    return parkedVehicle;
}

bool ParkingSpot::parkVehicle(std::shared_ptr<Vehicle> vehicle) {
    if (isOccupied || vehicle->getType() != spotType) {
        return false;
    }
    parkedVehicle = vehicle;
    isOccupied = true;
    return true;
}

void ParkingSpot::removeVehicle() {
    parkedVehicle = nullptr;
    isOccupied = false;
} 