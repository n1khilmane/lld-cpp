#pragma once
#include "Vehicle.hpp"
#include "ParkingTicket.hpp"
#include <memory>

class Entrance {
private:
    int id;

public:
    Entrance(int entranceId) : id(entranceId) {}
    int getId() const { return id; }
    std::shared_ptr<ParkingTicket> getTicket(std::shared_ptr<Vehicle> vehicle);
}; 