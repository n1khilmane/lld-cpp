#include "../include/ParkingLot.hpp"
#include <iostream>

ParkingLot& ParkingLot::getInstance(int parkingLotId,
                                   const std::string& parkingLotName,
                                   const std::string& parkingLotAddress,
                                   const ParkingRate& rate) {
    static ParkingLot instance(parkingLotId, parkingLotName, parkingLotAddress, rate);
    return instance;
}

bool ParkingLot::addEntrance(std::shared_ptr<Entrance> entrance) {
    if (!entrance) return false;
    entrances[std::to_string(entrance->getId())] = entrance;
    return true;
}

bool ParkingLot::addExit(std::shared_ptr<Exit> exit) {
    if (!exit) return false;
    exits[std::to_string(exit->getId())] = exit;
    return true;
}

std::shared_ptr<ParkingTicket> ParkingLot::getParkingTicket(std::shared_ptr<Vehicle> vehicle) {
    if (!vehicle) return nullptr;
    
    // Create a new ticket
    auto entrance = entrances.begin()->second; // Use first entrance for simplicity
    auto ticket = std::make_shared<ParkingTicket>(tickets.size() + 1, vehicle, entrance);
    
    // Store the ticket
    tickets[std::to_string(ticket->getTicketNo())] = ticket;
    
    return ticket;
}

bool ParkingLot::isFull(std::shared_ptr<ParkingSpot> type) {
    // Implementation to check if parking lot is full for a specific spot type
    return false;
} 