#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

enum CarType { SEDAN, SUV, HATCHBACK };
enum BookingStatus { ACTIVE, CANCELLED };

class Car {
public:
    int carId;
    string model;
    CarType type;
    string location;
    bool available;

    Car(int id, string m, CarType t, string loc) :
        carId(id), model(m), type(t), location(loc), available(true) {}

    bool isAvailable() const {
        return available;
    }
};

class Booking {
public:
    int bookingId;
    int userId;
    int carId;
    string startDate;
    string endDate;
    BookingStatus status;

    Booking(int id, int uId, int cId, string s, string e) :
        bookingId(id), userId(uId), carId(cId), startDate(s), endDate(e), status(ACTIVE) {}
};

class CarInventory {
    vector<Car> cars;

public:
    void addCar(Car car) {
        cars.push_back(car);
    }

    void removeCar(int carId) {
        cars.erase(remove_if(cars.begin(), cars.end(),
            [&](Car& c) { return c.carId == carId; }), cars.end());
    }

    vector<Car> search(string loc, CarType type) {
        vector<Car> result;
        for (auto& c : cars) {
            if (c.location == loc && c.type == type && c.isAvailable()) {
                result.push_back(c);
            }
        }
        return result;
    }

    void setAvailability(int carId, bool avail) {
        for (auto& c : cars) {
            if (c.carId == carId) {
                c.available = avail;
                return;
            }
        }
    }
};

class BookingManager {
    vector<Booking> bookings;
    int nextBookingId = 1;

public:
    Booking makeBooking(int userId, Car& car, string startDate, string endDate) {
        Booking b(nextBookingId++, userId, car.carId, startDate, endDate);
        bookings.push_back(b);
        return b;
    }

    void cancelBooking(int bookingId) {
        for (auto& b : bookings) {
            if (b.bookingId == bookingId) {
                b.status = CANCELLED;
                return;
            }
        }
    }
};

class User {
public:
    int userId;
    string name;

    User(int id, string n) : userId(id), name(n) {}

    vector<Car> searchCars(CarInventory& inventory, string loc, CarType type) {
        return inventory.search(loc, type);
    }

    Booking bookCar(CarInventory& inventory, BookingManager& bm, Car& car, string s, string e) {
        inventory.setAvailability(car.carId, false);
        return bm.makeBooking(userId, car, s, e);
    }
};

class Admin : public User {
public:
    Admin(int id, string n) : User(id, n) {}

    void addCar(CarInventory& inventory, Car car) {
        inventory.addCar(car);
    }

    void removeCar(CarInventory& inventory, int carId) {
        inventory.removeCar(carId);
    }
};

// Example usage (can be commented in interview):
/*
int main() {
    CarInventory inventory;
    BookingManager bm;
    Admin admin(1, "Alice");
    User user(2, "Bob");

    admin.addCar(inventory, Car(101, "Toyota", SEDAN, "NYC"));
    admin.addCar(inventory, Car(102, "Ford", SUV, "NYC"));

    auto cars = user.searchCars(inventory, "NYC", SEDAN);
    if (!cars.empty()) {
        Booking b = user.bookCar(inventory, bm, cars[0], "2023-10-01", "2023-10-05");
        cout << "Booked carId: " << b.carId << " by userId: " << b.userId << endl;
    }
}
*/
