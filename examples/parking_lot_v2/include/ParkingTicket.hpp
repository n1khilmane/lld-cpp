#pragma once
#include "Vehicle.hpp"
#include "Payment.hpp"
#include <memory>
#include <ctime>

class Entrance;
class Exit;

class ParkingTicket {
private:
    int ticketNo;
    time_t timestamp;
    time_t exitTime;
    double amount;
    bool status;
    std::shared_ptr<Vehicle> vehicle;
    std::shared_ptr<Payment> payment;
    std::shared_ptr<Entrance> entrance;
    std::shared_ptr<Exit> exitIns;

public:
    ParkingTicket(int ticketNumber, std::shared_ptr<Vehicle> v, 
                  std::shared_ptr<Entrance> ent)
        : ticketNo(ticketNumber), timestamp(time(nullptr)), exitTime(0),
          amount(0.0), status(false), vehicle(v), payment(nullptr),
          entrance(ent), exitIns(nullptr) {}

    int getTicketNo() const { return ticketNo; }
    time_t getTimestamp() const { return timestamp; }
    time_t getExitTime() const { return exitTime; }
    double getAmount() const { return amount; }
    bool getStatus() const { return status; }
    std::shared_ptr<Vehicle> getVehicle() const { return vehicle; }
    std::shared_ptr<Payment> getPayment() const { return payment; }
    std::shared_ptr<Entrance> getEntrance() const { return entrance; }
    std::shared_ptr<Exit> getExit() const { return exitIns; }

    void setExitTime(time_t time) { exitTime = time; }
    void setAmount(double amt) { amount = amt; }
    void setStatus(bool stat) { status = stat; }
    void setPayment(std::shared_ptr<Payment> pay) { payment = pay; }
    void setExit(std::shared_ptr<Exit> exit) { exitIns = exit; }
}; 