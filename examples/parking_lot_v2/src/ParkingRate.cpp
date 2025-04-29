#include "../include/ParkingRate.hpp"

double ParkingRate::calculate(double hoursParked) const {
    return hoursParked * rate;
} 