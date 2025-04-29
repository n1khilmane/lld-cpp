#pragma once
#include <ctime>

class ParkingRate {
private:
    double hours;
    double rate;

public:
    ParkingRate(double h, double r) : hours(h), rate(r) {}
    double calculate(double hoursParked) const;
}; 