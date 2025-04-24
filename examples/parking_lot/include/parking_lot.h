#pragma once

#include <string>
#include <vector>
#include <memory>

enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};

class Vehicle {
public:
    Vehicle(VehicleType type, const std::string& licensePlate);
    VehicleType getType() const;
    const std::string& getLicensePlate() const;

private:
    VehicleType type;
    std::string licensePlate;
};

class ParkingSpot {
public:
    ParkingSpot(int id, VehicleType type);
    bool isOccupied() const;
    void parkVehicle(std::shared_ptr<Vehicle> vehicle);
    void removeVehicle();
    int getId() const;
    VehicleType getType() const;

private:
    int id;
    VehicleType type;
    std::shared_ptr<Vehicle> vehicle;
};

class ParkingLot {
public:
    ParkingLot(int numSpots);
    bool parkVehicle(std::shared_ptr<Vehicle> vehicle);
    bool removeVehicle(const std::string& licensePlate);
    void displayStatus() const;

private:
    std::vector<ParkingSpot> spots;
}; 