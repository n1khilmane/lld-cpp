#include "../include/Entrance.hpp"
#include "../include/ParkingLot.hpp"

std::shared_ptr<ParkingTicket> Entrance::getTicket(std::shared_ptr<Vehicle> vehicle) {
    ParkingLot& parkingLot = ParkingLot::getInstance();
    return parkingLot.getParkingTicket(vehicle);
} 