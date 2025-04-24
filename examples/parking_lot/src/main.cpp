#include "parking_lot.h"
#include <iostream>

int main() {
    // Create a parking lot with 6 spots
    ParkingLot parkingLot(6);

    // Create some vehicles
    auto car1 = std::make_shared<Vehicle>(VehicleType::CAR, "CAR001");
    auto bike1 = std::make_shared<Vehicle>(VehicleType::BIKE, "BIKE001");
    auto truck1 = std::make_shared<Vehicle>(VehicleType::TRUCK, "TRUCK001");

    // Park vehicles
    std::cout << "Parking vehicles...\n";
    parkingLot.parkVehicle(car1);
    parkingLot.parkVehicle(bike1);
    parkingLot.parkVehicle(truck1);

    // Display parking lot status
    parkingLot.displayStatus();

    // Remove a vehicle
    std::cout << "\nRemoving vehicle with license plate BIKE001...\n";
    parkingLot.removeVehicle("BIKE001");

    // Display updated status
    parkingLot.displayStatus();

    return 0;
} 