#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

enum RoomType { SINGLE, DOUBLE, SUITE };

class Room {
public:
    int roomNumber;
    RoomType type;
    bool isBooked;

    Room(int num, RoomType t) : roomNumber(num), type(t), isBooked(false) {}
};

class Customer {
public:
    int customerId;
    string name;

    Customer(int id, string n) : customerId(id), name(n) {}
};

class Booking {
public:
    int bookingId;
    int customerId;
    int roomNumber;

    Booking(int id, int cid, int rno) : bookingId(id), customerId(cid), roomNumber(rno) {}
};

class Hotel {
private:
    vector<Room> rooms;
    vector<Booking> bookings;
    int bookingCounter = 1;

public:
    void addRoom(int number, RoomType type) {
        rooms.push_back(Room(number, type));
    }

    bool bookRoom(int customerId, RoomType type) {
        for (auto& room : rooms) {
            if (!room.isBooked && room.type == type) {
                room.isBooked = true;
                bookings.push_back(Booking(bookingCounter++, customerId, room.roomNumber));
                cout << "Room " << room.roomNumber << " booked for customer " << customerId << endl;
                return true;
            }
        }
        cout << "No available rooms of requested type.\n";
        return false;
    }

    void checkout(int roomNumber) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber) {
                room.isBooked = false;
                cout << "Room " << roomNumber << " is now available.\n";
                return;
            }
        }
        cout << "Room not found.\n";
    }

    void listBookings() {
        for (auto& b : bookings) {
            cout << "BookingID: " << b.bookingId << ", CustomerID: " << b.customerId
                 << ", Room: " << b.roomNumber << endl;
        }
    }

    void availableRooms(RoomType type) {
        for (auto& room : rooms) {
            if (!room.isBooked && room.type == type) {
                cout << "Available Room: " << room.roomNumber << endl;
            }
        }
    }
};

class HotelManagementSystem {
private:
    Hotel hotel;
    vector<Customer> customers;

public:
    void addCustomer(int id, string name) {
        customers.push_back(Customer(id, name));
    }

    void addRoom(int number, RoomType type) {
        hotel.addRoom(number, type);
    }

    void bookRoom(int customerId, RoomType type) {
        hotel.bookRoom(customerId, type);
    }

    void checkout(int roomNumber) {
        hotel.checkout(roomNumber);
    }

    void showBookings() {
        hotel.listBookings();
    }

    void showAvailableRooms(RoomType type) {
        hotel.availableRooms(type);
    }
};

// Sample usage
int main() {
    HotelManagementSystem hms;
    hms.addCustomer(1, "Alice");
    hms.addCustomer(2, "Bob");

    hms.addRoom(101, SINGLE);
    hms.addRoom(102, DOUBLE);
    hms.addRoom(201, SINGLE);
    hms.addRoom(202, SUITE);

    hms.bookRoom(1, SINGLE);
    hms.bookRoom(2, SUITE);
    hms.bookRoom(2, SINGLE); // Should book the second single room

    hms.showAvailableRooms(SINGLE);

    hms.checkout(201);
    hms.showAvailableRooms(SINGLE);

    hms.showBookings();

    return 0;
}
