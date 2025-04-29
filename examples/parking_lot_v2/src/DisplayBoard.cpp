#include "../include/DisplayBoard.hpp"
#include <iostream>

void DisplayBoard::addParkingSpot(std::shared_ptr<ParkingSpot> spot) {
    parkingSpots.push_back(spot);
}

void DisplayBoard::showFreeSlot() {
    std::cout << "\nParking Spot Status:\n";
    std::cout << "-------------------\n";
    
    for (const auto& spot : parkingSpots) {
        std::cout << "Spot " << spot->getId() << ": ";
        if (spot->getIsFree()) {
            std::cout << "Available";
        } else {
            std::cout << "Occupied by " << spot->getVehicle()->getLicenseNo();
        }
        std::cout << "\n";
    }
} 