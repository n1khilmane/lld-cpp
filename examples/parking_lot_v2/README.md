# Parking Lot System

A modern C++ implementation of a parking lot management system using object-oriented design principles and design patterns.

## Features

- Multiple types of parking spots (Handicapped, Compact, Large, Motorcycle)
- Different vehicle types (Car, Van, Truck, Motorcycle)
- Multiple payment methods (Cash, Credit Card)
- Ticket-based parking management
- Real-time display board for parking spot status
- Access control through admin and attendant accounts
- Entry/Exit point management
- Dynamic pricing based on parking duration

## System Design

### Core Components

1. **Vehicle System**
   - Abstract `Vehicle` base class
   - Concrete implementations: `Car`, `Van`, `Truck`, `Motorcycle`
   - Each vehicle has a unique license plate

2. **Parking Spot System**
   - Abstract `ParkingSpot` base class
   - Concrete implementations: `HandicappedSpot`, `CompactSpot`, `LargeSpot`, `MotorcycleSpot`
   - Tracks occupancy status and parked vehicle

3. **Payment System**
   - Abstract `Payment` base class
   - Concrete implementations: `Cash`, `CreditCard`
   - Tracks payment status and amount

4. **Account Management**
   - Abstract `Account` base class
   - Concrete implementations: `Admin`, `ParkingAttendant`
   - Manages user roles and permissions

5. **Ticket Management**
   - `ParkingTicket` class for tracking parking sessions
   - Links vehicle, payment, and parking duration

6. **Entry/Exit System**
   - `Entrance` class for vehicle entry and ticket generation
   - `Exit` class for ticket validation and vehicle exit

7. **Display System**
   - `DisplayBoard` class for showing real-time parking status
   - Shows available and occupied spots

8. **Rate Management**
   - `ParkingRate` class for fee calculation
   - Supports time-based pricing

### Design Patterns Used

1. **Singleton Pattern**
   - Used in `ParkingLot` class
   - Ensures single system-wide parking lot instance

2. **Factory Pattern**
   - Used for creating vehicles and parking spots
   - Enables extensibility for new types

3. **Strategy Pattern**
   - Used in payment processing
   - Allows different payment methods

4. **Observer Pattern**
   - Used in display board implementation
   - Real-time updates of parking status

## Class Relationships

```
Vehicle (Abstract) ──┬── Car
                    ├── Van
                    ├── Truck
                    └── Motorcycle

ParkingSpot (Abstract) ──┬── HandicappedSpot
                        ├── CompactSpot
                        ├── LargeSpot
                        └── MotorcycleSpot

Payment (Abstract) ──┬── Cash
                    └── CreditCard

Account (Abstract) ──┬── Admin
                    └── ParkingAttendant
```

## Building and Running

### Prerequisites
- CMake (version 3.10 or higher)
- C++17 compatible compiler
- Make or equivalent build system

### Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

### Running the Program
```bash
./parking_lot_v2
```

## Usage Example

```cpp
// Get parking lot instance
ParkingLot& parkingLot = ParkingLot::getInstance();

// Create and add entrance/exit points
auto entrance = std::make_shared<Entrance>(1);
auto exit = std::make_shared<Exit>(1);
parkingLot.addEntrance(entrance);
parkingLot.addExit(exit);

// Create parking spots
auto compactSpot = std::make_shared<CompactSpot>(1);

// Create and park a vehicle
auto car = std::make_shared<Car>("C001");
compactSpot->assignVehicle(car);

// Get parking ticket
auto ticket = entrance->getTicket(car);

// Process payment
auto payment = std::make_shared<Cash>(10.0);
payment->initiateTransaction();
ticket->setPayment(payment);
ticket->setStatus(true);

// Validate ticket at exit
exit->validateTicket(ticket);
```

## Future Enhancements

1. **Parking Management**
   - Multiple floors/levels support
   - Reserved parking spots
   - Valet parking service

2. **Payment System**
   - Integration with real payment gateways
   - Subscription/membership support
   - Dynamic pricing based on demand

3. **Monitoring & Analytics**
   - Occupancy statistics
   - Revenue reports
   - Peak hour analysis

4. **User Experience**
   - Mobile app integration
   - Automated license plate recognition
   - Smart spot allocation

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details. 