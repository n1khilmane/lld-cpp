#pragma once
#include <string>

enum class VehicleType {
    MOTORCYCLE,
    CAR,
    BUS
};

class Vehicle {
private:
    std::string licensePlate;
    VehicleType type;

public:
    Vehicle(const std::string& plate, VehicleType vehicleType);
    virtual ~Vehicle() = default;

    std::string getLicensePlate() const;
    VehicleType getType() const;
}; 