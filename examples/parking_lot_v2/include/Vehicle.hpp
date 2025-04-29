#pragma once
#include <string>
#include <memory>

class ParkingTicket;

class Vehicle {
protected:
    std::string licenseNo;

public:
    Vehicle(const std::string& license) : licenseNo(license) {}
    virtual ~Vehicle() = default;

    std::string getLicenseNo() const { return licenseNo; }
    virtual void assignTicket(std::shared_ptr<ParkingTicket> ticket) = 0;
};

class Car : public Vehicle {
public:
    Car(const std::string& license) : Vehicle(license) {}
    void assignTicket(std::shared_ptr<ParkingTicket> ticket) override;
};

class Van : public Vehicle {
public:
    Van(const std::string& license) : Vehicle(license) {}
    void assignTicket(std::shared_ptr<ParkingTicket> ticket) override;
};

class Truck : public Vehicle {
public:
    Truck(const std::string& license) : Vehicle(license) {}
    void assignTicket(std::shared_ptr<ParkingTicket> ticket) override;
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(const std::string& license) : Vehicle(license) {}
    void assignTicket(std::shared_ptr<ParkingTicket> ticket) override;
}; 