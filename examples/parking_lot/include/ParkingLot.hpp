#pragma once
#include "ParkingSpot.hpp"
#include "Vehicle.hpp"
#include <vector>
#include <unordered_map>
#include <memory>

class ParkingLot {
private:
    std::vector<std::shared_ptr<ParkingSpot>> parkingSpots;
    std::unordered_map<std::string, int> vehicleToSpotMap; // license plate to spot number

public:
    ParkingLot(int motorcycleSpots, int carSpots, int busSpots);
    virtual ~ParkingLot() = default;

    bool parkVehicle(std::shared_ptr<Vehicle> vehicle);
    bool removeVehicle(const std::string& licensePlate);
    std::shared_ptr<ParkingSpot> findSpot(const std::string& licensePlate);
    int getAvailableSpots(VehicleType type) const;
    void displayParkingStatus() const;
}; 