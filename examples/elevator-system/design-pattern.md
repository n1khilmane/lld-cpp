# Design Patterns in Elevator System

## 1. Singleton Pattern
### For ElevatorSystem (Central Controller)

#### What it solves
- Ensures there's only one instance of the ElevatorSystem managing all elevators

#### Implementation
```cpp
class ElevatorSystem {
private:
    static ElevatorSystem* instance;
    ElevatorSystem() { /* private constructor */ }

public:
    static ElevatorSystem* getInstance() {
        if (!instance) {
            instance = new ElevatorSystem();
        }
        return instance;
    }
};
```

#### Why it fits
- You want one point of control over all elevators
- Prevents multiple conflicting controllers

---

## 2. Strategy Pattern
### For Scheduler Logic

#### What it solves
- Allows you to swap request assignment strategies
- Supports multiple algorithms:
  - Nearest elevator
  - Load-balancing
  - Zone-based

#### Implementation
```cpp
class SchedulingStrategy {
public:
    virtual int selectElevator(
        const vector<Elevator>& elevators,
        int floor,
        Direction dir
    ) = 0;
};

class NearestElevatorStrategy : public SchedulingStrategy {
    // Implementation details
};

class LoadBalancedStrategy : public SchedulingStrategy {
    // Implementation details
};
```

#### Why it fits
- Lets you easily change how elevators are selected without modifying core logic
- Makes your code open for extension, closed for modification (Open/Closed Principle)

---

## 3. Observer Pattern
### For Event Notification

#### What it solves
- Lets other parts of your system react to elevator events:
  - Door opened
  - Elevator reached floor
  - Status changes

#### Implementation
```cpp
class ElevatorObserver {
public:
    virtual void onFloorReached(int elevatorId, int floor) = 0;
};

class Logger : public ElevatorObserver {
    // Implementation details
};

class UIUpdater : public ElevatorObserver {
    // Implementation details
};
```

#### Observer Registration
```cpp
void notifyFloorReached() {
    for (auto obs : observers) {
        obs->onFloorReached(id, currentFloor);
    }
}
```

#### Why it fits
- Decouples elevator logic from external effects (logging, UI updates, alarms)
- Enables easy addition of new observers without modifying elevator code

---

## 4. Factory Pattern
### For Creating Different Elevator Types

#### What it solves
- Encapsulates the logic of creating different elevator types:
  - Service Elevator
  - Express Elevator
  - Standard Elevator

#### Implementation
```cpp
class ElevatorFactory {
public:
    static Elevator createElevator(string type, int id) {
        if (type == "Service") {
            return ServiceElevator(id);
        }
        if (type == "Express") {
            return ExpressElevator(id);
        }
        return StandardElevator(id);
    }
};
```

#### Why it fits
- Allows easy addition of new elevator types without changing core system logic
- Centralizes elevator creation logic

---

## 5. Decorator Pattern
### For Dynamic Member Features

#### What it solves
- Adds optional features to members without modifying base class
- Supports features like:
  - Premium membership
  - Priority borrowing
  - Special access privileges

#### Implementation
```cpp
class MemberDecorator : public Member {
protected:
    Member* member;
public:
    MemberDecorator(Member* m) : Member(m->userId, m->name), member(m) {}
};

class PremiumMember : public MemberDecorator {
public:
    PremiumMember(Member* m) : MemberDecorator(m) {}

    void accessLounge() {
        cout << "Accessing premium lounge\n";
    }
};
```

#### Why it fits
- Allows dynamic addition of member features
- Maintains single responsibility principle
- Easy to add new member types without modifying existing code

---

## 6. Command Pattern
### For Action Management

#### What it solves
- Encapsulates operations as objects
- Enables features like:
  - Undo for borrow/return operations
  - Action queuing
  - Command history

#### Implementation
```cpp
class Command {
public:
    virtual void execute() = 0;
};

class BorrowCommand : public Command {
    Library* lib;
    string memberId, barcode, date;
public:
    BorrowCommand(Library* l, string m, string b, string d) 
        : lib(l), memberId(m), barcode(b), date(d) {}
    
    void execute() override {
        lib->borrowBook(memberId, barcode, date);
    }
};
```

#### Why it fits
- Perfect for building admin panels
- Enables action history tracking
- Supports undo/redo functionality

---

## Pattern Selection Guide

### Recommended Patterns for SDE1 Interviews

| Pattern    | Ease of Explanation | Library Relevance | Design Thinking |
|------------|---------------------|-------------------|-----------------|
| Factory    | ✅                  | ✅                | ✅              |
| Strategy   | ✅                  | ✅                | ✅              |
| Singleton  | ✅                  | ✅                | ✅              |
| Observer   | Medium              | ✅                | ✅              |
| Decorator  | Medium-Hard         | ✅ (Premium)      | ✅              |