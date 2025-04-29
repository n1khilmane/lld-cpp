#pragma once
#include "Vehicle.hpp"
#include <memory>

class ParkingSpot {
protected:
    int id;
    bool isFree;
    std::shared_ptr<Vehicle> vehicle;

public:
    ParkingSpot(int spotId) : id(spotId), isFree(true), vehicle(nullptr) {}
    virtual ~ParkingSpot() = default;

    int getId() const { return id; }
    bool getIsFree() const { return isFree; }
    std::shared_ptr<Vehicle> getVehicle() const { return vehicle; }

    virtual bool assignVehicle(std::shared_ptr<Vehicle> vehicle) = 0;
    bool removeVehicle() {
        if (!isFree) {
            vehicle = nullptr;
            isFree = true;
            return true;
        }
        return false;
    }
};

class HandicappedSpot : public ParkingSpot {
public:
    HandicappedSpot(int spotId) : ParkingSpot(spotId) {}
    bool assignVehicle(std::shared_ptr<Vehicle> vehicle) override;
};

class CompactSpot : public ParkingSpot {
public:
    CompactSpot(int spotId) : ParkingSpot(spotId) {}
    bool assignVehicle(std::shared_ptr<Vehicle> vehicle) override;
};

class LargeSpot : public ParkingSpot {
public:
    LargeSpot(int spotId) : ParkingSpot(spotId) {}
    bool assignVehicle(std::shared_ptr<Vehicle> vehicle) override;
};

class MotorcycleSpot : public ParkingSpot {
public:
    MotorcycleSpot(int spotId) : ParkingSpot(spotId) {}
    bool assignVehicle(std::shared_ptr<Vehicle> vehicle) override;
}; 