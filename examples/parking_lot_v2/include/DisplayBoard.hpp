#pragma once
#include "ParkingSpot.hpp"
#include <vector>
#include <memory>

class DisplayBoard {
private:
    int id;
    std::vector<std::shared_ptr<ParkingSpot>> parkingSpots;

public:
    DisplayBoard(int boardId) : id(boardId) {}
    int getId() const { return id; }
    void addParkingSpot(std::shared_ptr<ParkingSpot> spot);
    void showFreeSlot();
}; 