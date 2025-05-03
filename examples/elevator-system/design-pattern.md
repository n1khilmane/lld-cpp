# Design Patterns in Elevator System

## 1. Singleton Pattern — For ElevatorSystem (Central Controller)

### What it solves
- Ensures there's only one instance of the ElevatorSystem managing all elevators

### Implementation
```cpp
class ElevatorSystem {
private:
    static ElevatorSystem* instance;
    ElevatorSystem() { /* private constructor */ }

public:
    static ElevatorSystem* getInstance() {
        if (!instance) instance = new ElevatorSystem();
        return instance;
    }
};
```

### Why it fits
- You want one point of control over all elevators
- Prevents multiple conflicting controllers

## 2. Strategy Pattern — For Scheduler Logic

### What it solves
- Allows you to swap request assignment strategies (e.g., nearest elevator, load-balancing, zone-based)

### Implementation
```cpp
class SchedulingStrategy {
public:
    virtual int selectElevator(const vector<Elevator>&, int floor, Direction dir) = 0;
};

class NearestElevatorStrategy : public SchedulingStrategy { ... };
class LoadBalancedStrategy : public SchedulingStrategy { ... };
```

### Why it fits
- Lets you easily change how elevators are selected without modifying core logic
- Makes your code open for extension, closed for modification (Open/Closed Principle)

## 3. Observer Pattern — For Event Notification

### What it solves
- Lets other parts of your system react to elevator events (e.g., "door opened", "elevator reached floor 5")

### Implementation
```cpp
class ElevatorObserver {
public:
    virtual void onFloorReached(int elevatorId, int floor) = 0;
};

class Logger : public ElevatorObserver { ... };
class UIUpdater : public ElevatorObserver { ... };
```

### Observer Registration
```cpp
void notifyFloorReached() {
    for (auto obs : observers)
        obs->onFloorReached(id, currentFloor);
}
```

### Why it fits
- Decouples elevator logic from external effects (like logging, UI updates, alarms)

## 4. Factory Pattern — For Creating Different Elevator Types

### What it solves
- Encapsulates the logic of creating different elevator types (e.g., ServiceElevator, ExpressElevator)

### Implementation
```cpp
class ElevatorFactory {
public:
    static Elevator createElevator(string type, int id) {
        if (type == "Service") return ServiceElevator(id);
        if (type == "Express") return ExpressElevator(id);
        return StandardElevator(id);
    }
};
```

### Why it fits
- Allows easy addition of new elevator types without changing core system logic

## Summary Table

| Pattern | Use Case | Benefits |
|---------|----------|----------|
| Singleton | One global elevator system | Centralized control |
| Strategy | Pluggable scheduling algorithms | Easy to extend and test |
| Observer | Notify UI/log when events happen | Loose coupling with external systems |
| Factory | Create elevators based on type/config | Clean object creation, extensibility |