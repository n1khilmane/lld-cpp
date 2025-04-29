#include "../include/Exit.hpp"
#include <iostream>

void Exit::validateTicket(std::shared_ptr<ParkingTicket> ticket) {
    if (!ticket) {
        std::cout << "Invalid ticket!" << std::endl;
        return;
    }

    if (!ticket->getStatus()) {
        std::cout << "Ticket not paid!" << std::endl;
        return;
    }

    std::cout << "Ticket validated. Vehicle can exit." << std::endl;
} 