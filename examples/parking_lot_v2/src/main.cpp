#include "../include/ParkingLot.hpp"
#include "../include/Vehicle.hpp"
#include "../include/ParkingSpot.hpp"
#include "../include/Entrance.hpp"
#include "../include/Exit.hpp"
#include "../include/DisplayBoard.hpp"
#include "../include/Payment.hpp"
#include <iostream>
#include <memory>

int main() {
    // Get parking lot instance
    ParkingLot& parkingLot = ParkingLot::getInstance();
    
    // Create entrance and exit
    auto entrance = std::make_shared<Entrance>(1);
    auto exit = std::make_shared<Exit>(1);
    
    // Add entrance and exit to parking lot
    parkingLot.addEntrance(entrance);
    parkingLot.addExit(exit);
    
    // Create display board
    auto displayBoard = std::make_shared<DisplayBoard>(1);
    
    // Create parking spots
    auto handicappedSpot = std::make_shared<HandicappedSpot>(1);
    auto compactSpot = std::make_shared<CompactSpot>(2);
    auto largeSpot = std::make_shared<LargeSpot>(3);
    auto motorcycleSpot = std::make_shared<MotorcycleSpot>(4);
    
    // Add spots to display board
    displayBoard->addParkingSpot(handicappedSpot);
    displayBoard->addParkingSpot(compactSpot);
    displayBoard->addParkingSpot(largeSpot);
    displayBoard->addParkingSpot(motorcycleSpot);
    
    // Create vehicles
    auto car = std::make_shared<Car>("C001");
    auto van = std::make_shared<Van>("V001");
    auto truck = std::make_shared<Truck>("T001");
    auto motorcycle = std::make_shared<Motorcycle>("M001");
    
    // Park vehicles
    std::cout << "Parking vehicles...\n";
    compactSpot->assignVehicle(car);
    largeSpot->assignVehicle(van);
    largeSpot->assignVehicle(truck);
    motorcycleSpot->assignVehicle(motorcycle);
    
    // Show parking status
    displayBoard->showFreeSlot();
    
    // Get parking tickets
    auto carTicket = entrance->getTicket(car);
    auto vanTicket = entrance->getTicket(van);
    auto truckTicket = entrance->getTicket(truck);
    auto motorcycleTicket = entrance->getTicket(motorcycle);
    
    // Process payments
    auto carPayment = std::make_shared<Cash>(10.0);
    auto vanPayment = std::make_shared<CreditCard>(20.0, "1234-5678-9012-3456", "John Doe", "12/25");
    
    carPayment->initiateTransaction();
    vanPayment->initiateTransaction();
    
    carTicket->setPayment(carPayment);
    vanTicket->setPayment(vanPayment);
    
    carTicket->setStatus(true);
    vanTicket->setStatus(true);
    
    // Validate tickets at exit
    std::cout << "\nValidating tickets at exit...\n";
    exit->validateTicket(carTicket);
    exit->validateTicket(vanTicket);
    exit->validateTicket(truckTicket);
    exit->validateTicket(motorcycleTicket);
    
    return 0;
} 