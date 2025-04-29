#pragma once
#include "ParkingSpot.hpp"
#include "Vehicle.hpp"
#include "ParkingTicket.hpp"
#include "Entrance.hpp"
#include "Exit.hpp"
#include "ParkingRate.hpp"
#include <string>
#include <map>
#include <memory>

class ParkingLot {
private:
    int id;
    std::string name;
    std::string address;
    ParkingRate parkingRate;
    std::map<std::string, std::shared_ptr<Entrance>> entrances;
    std::map<std::string, std::shared_ptr<Exit>> exits;
    std::map<std::string, std::shared_ptr<ParkingTicket>> tickets;

    // Private constructor for Singleton
    ParkingLot(int parkingLotId, const std::string& parkingLotName,
               const std::string& parkingLotAddress, const ParkingRate& rate)
        : id(parkingLotId), name(parkingLotName), address(parkingLotAddress), parkingRate(rate) {}

    // Delete copy constructor and assignment operator
    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

public:
    static ParkingLot& getInstance(int parkingLotId = 1,
                                 const std::string& parkingLotName = "Main Parking Lot",
                                 const std::string& parkingLotAddress = "123 Main St",
                                 const ParkingRate& rate = ParkingRate(1.0, 10.0));

    bool addEntrance(std::shared_ptr<Entrance> entrance);
    bool addExit(std::shared_ptr<Exit> exit);
    std::shared_ptr<ParkingTicket> getParkingTicket(std::shared_ptr<Vehicle> vehicle);
    bool isFull(std::shared_ptr<ParkingSpot> type);
}; 