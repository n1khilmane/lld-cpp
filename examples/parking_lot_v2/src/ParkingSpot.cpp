#include "../include/ParkingSpot.hpp"

bool HandicappedSpot::assignVehicle(std::shared_ptr<Vehicle> vehicle) {
    if (!isFree) return false;
    this->vehicle = vehicle;
    isFree = false;
    return true;
}

bool CompactSpot::assignVehicle(std::shared_ptr<Vehicle> vehicle) {
    if (!isFree) return false;
    this->vehicle = vehicle;
    isFree = false;
    return true;
}

bool LargeSpot::assignVehicle(std::shared_ptr<Vehicle> vehicle) {
    if (!isFree) return false;
    this->vehicle = vehicle;
    isFree = false;
    return true;
}

bool MotorcycleSpot::assignVehicle(std::shared_ptr<Vehicle> vehicle) {
    if (!isFree) return false;
    this->vehicle = vehicle;
    isFree = false;
    return true;
} 