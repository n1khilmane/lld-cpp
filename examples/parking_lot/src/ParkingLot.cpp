#include "../include/ParkingLot.hpp"
#include <iostream>

ParkingLot::ParkingLot(int motorcycleSpots, int carSpots, int busSpots) {
    int spotNumber = 1;
    
    // Create motorcycle spots
    for (int i = 0; i < motorcycleSpots; ++i) {
        parkingSpots.push_back(std::make_shared<ParkingSpot>(spotNumber++, VehicleType::MOTORCYCLE));
    }
    
    // Create car spots
    for (int i = 0; i < carSpots; ++i) {
        parkingSpots.push_back(std::make_shared<ParkingSpot>(spotNumber++, VehicleType::CAR));
    }
    
    // Create bus spots
    for (int i = 0; i < busSpots; ++i) {
        parkingSpots.push_back(std::make_shared<ParkingSpot>(spotNumber++, VehicleType::BUS));
    }
}

bool ParkingLot::parkVehicle(std::shared_ptr<Vehicle> vehicle) {
    // Check if vehicle is already parked
    if (vehicleToSpotMap.find(vehicle->getLicensePlate()) != vehicleToSpotMap.end()) {
        return false;
    }

    // Find an available spot for the vehicle type
    for (const auto& spot : parkingSpots) {
        if (!spot->getIsOccupied() && spot->getSpotType() == vehicle->getType()) {
            if (spot->parkVehicle(vehicle)) {
                vehicleToSpotMap[vehicle->getLicensePlate()] = spot->getSpotNumber();
                return true;
            }
        }
    }
    return false;
}

bool ParkingLot::removeVehicle(const std::string& licensePlate) {
    auto it = vehicleToSpotMap.find(licensePlate);
    if (it == vehicleToSpotMap.end()) {
        return false;
    }

    int spotNumber = it->second;
    for (const auto& spot : parkingSpots) {
        if (spot->getSpotNumber() == spotNumber) {
            spot->removeVehicle();
            vehicleToSpotMap.erase(it);
            return true;
        }
    }
    return false;
}

std::shared_ptr<ParkingSpot> ParkingLot::findSpot(const std::string& licensePlate) {
    auto it = vehicleToSpotMap.find(licensePlate);
    if (it == vehicleToSpotMap.end()) {
        return nullptr;
    }

    int spotNumber = it->second;
    for (const auto& spot : parkingSpots) {
        if (spot->getSpotNumber() == spotNumber) {
            return spot;
        }
    }
    return nullptr;
}

int ParkingLot::getAvailableSpots(VehicleType type) const {
    int count = 0;
    for (const auto& spot : parkingSpots) {
        if (!spot->getIsOccupied() && spot->getSpotType() == type) {
            count++;
        }
    }
    return count;
}

void ParkingLot::displayParkingStatus() const {
    std::cout << "\nParking Lot Status:\n";
    std::cout << "-------------------\n";
    
    for (const auto& spot : parkingSpots) {
        std::cout << "Spot " << spot->getSpotNumber() << " (";
        switch (spot->getSpotType()) {
            case VehicleType::MOTORCYCLE:
                std::cout << "Motorcycle";
                break;
            case VehicleType::CAR:
                std::cout << "Car";
                break;
            case VehicleType::BUS:
                std::cout << "Bus";
                break;
        }
        std::cout << "): ";
        
        if (spot->getIsOccupied()) {
            std::cout << "Occupied by " << spot->getParkedVehicle()->getLicensePlate();
        } else {
            std::cout << "Available";
        }
        std::cout << "\n";
    }
} 