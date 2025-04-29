#pragma once
#include "Vehicle.hpp"
#include <memory>

class ParkingSpot {
private:
    int spotNumber;
    VehicleType spotType;
    bool isOccupied;
    std::shared_ptr<Vehicle> parkedVehicle;

public:
    ParkingSpot(int number, VehicleType type);
    virtual ~ParkingSpot() = default;

    int getSpotNumber() const;
    VehicleType getSpotType() const;
    bool getIsOccupied() const;
    std::shared_ptr<Vehicle> getParkedVehicle() const;

    bool parkVehicle(std::shared_ptr<Vehicle> vehicle);
    void removeVehicle();
}; 