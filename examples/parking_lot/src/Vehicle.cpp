#include "../include/Vehicle.hpp"

Vehicle::Vehicle(const std::string& plate, VehicleType vehicleType)
    : licensePlate(plate), type(vehicleType) {}

std::string Vehicle::getLicensePlate() const {
    return licensePlate;
}

VehicleType Vehicle::getType() const {
    return type;
} 