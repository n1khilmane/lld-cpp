#include "../include/ParkingLot.hpp"
#include <iostream>

int main() {
    // Create a parking lot with 2 motorcycle spots, 3 car spots, and 1 bus spot
    ParkingLot parkingLot(2, 3, 1);
    
    // Create some vehicles
    auto motorcycle1 = std::make_shared<Vehicle>("M001", VehicleType::MOTORCYCLE);
    auto motorcycle2 = std::make_shared<Vehicle>("M002", VehicleType::MOTORCYCLE);
    auto car1 = std::make_shared<Vehicle>("C001", VehicleType::CAR);
    auto car2 = std::make_shared<Vehicle>("C002", VehicleType::CAR);
    auto bus1 = std::make_shared<Vehicle>("B001", VehicleType::BUS);
    
    // Park vehicles
    std::cout << "Parking vehicles...\n";
    parkingLot.parkVehicle(motorcycle1);
    parkingLot.parkVehicle(motorcycle2);
    parkingLot.parkVehicle(car1);
    parkingLot.parkVehicle(car2);
    parkingLot.parkVehicle(bus1);
    
    // Display parking status
    parkingLot.displayParkingStatus();
    
    // Remove a vehicle
    std::cout << "\nRemoving vehicle M001...\n";
    parkingLot.removeVehicle("M001");
    
    // Display updated status
    parkingLot.displayParkingStatus();
    
    // Try to park another motorcycle
    auto motorcycle3 = std::make_shared<Vehicle>("M003", VehicleType::MOTORCYCLE);
    std::cout << "\nTrying to park another motorcycle...\n";
    if (parkingLot.parkVehicle(motorcycle3)) {
        std::cout << "Successfully parked M003\n";
    } else {
        std::cout << "Failed to park M003 - no available spots\n";
    }
    
    // Display final status
    parkingLot.displayParkingStatus();
    
    return 0;
} 