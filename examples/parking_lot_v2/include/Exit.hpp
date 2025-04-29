#pragma once
#include "ParkingTicket.hpp"
#include <memory>

class Exit {
private:
    int id;

public:
    Exit(int exitId) : id(exitId) {}
    int getId() const { return id; }
    void validateTicket(std::shared_ptr<ParkingTicket> ticket);
}; 