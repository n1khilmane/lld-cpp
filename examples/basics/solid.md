# SOLID Principles in Object-Oriented Design

## Table of Contents
1. [Single Responsibility Principle (SRP)](#single-responsibility-principle-srp)
2. [Open Closed Principle (OCP)](#open-closed-principle-ocp)
3. [Liskov Substitution Principle (LSP)](#liskov-substitution-principle-lsp)
4. [Interface Segregation Principle (ISP)](#interface-segregation-principle-isp)
5. [Dependency Inversion Principle (DIP)](#dependency-inversion-principle-dip)

## Single Responsibility Principle (SRP)

### Definition
"A class should have only one reason to change." - Robert C. Martin

### Key Concepts
- Each class should have a single responsibility
- All methods and properties should be related to that responsibility
- Changes to one responsibility should not affect others

### Example
```cpp
// Bad Example - Multiple Responsibilities
class UserManager {
public:
    void createUser() { /* ... */ }
    void deleteUser() { /* ... */ }
    void sendEmail() { /* ... */ }
    void generateReport() { /* ... */ }
};

// Good Example - Single Responsibility
class UserManager {
public:
    void createUser() { /* ... */ }
    void deleteUser() { /* ... */ }
};

class EmailService {
public:
    void sendEmail() { /* ... */ }
};

class ReportGenerator {
public:
    void generateReport() { /* ... */ }
};
```

## Open Closed Principle (OCP)

### Definition
"Software entities should be open for extension but closed for modification." - Bertrand Meyer

### Key Concepts
- Classes should be extendable without modification
- Use abstraction and polymorphism
- Design for future changes

### Example
```cpp
// Bad Example - Not Open for Extension
class Rectangle {
public:
    double width;
    double height;
};

class AreaCalculator {
public:
    double calculateArea(Rectangle rectangle) {
        return rectangle.width * rectangle.height;
    }
};

// Good Example - Open for Extension
class Shape {
public:
    virtual double calculateArea() = 0;
};

class Rectangle : public Shape {
public:
    double width;
    double height;
    double calculateArea() override {
        return width * height;
    }
};

class Circle : public Shape {
public:
    double radius;
    double calculateArea() override {
        return 3.14 * radius * radius;
    }
};
```

## Liskov Substitution Principle (LSP)

### Definition
"Subtypes must be substitutable for their base types."

### Key Concepts
- Derived classes must be substitutable for their base classes
- Maintain behavioral compatibility
- Preserve contracts and invariants

### Example
```cpp
// Bad Example - Violates LSP
class Bird {
public:
    virtual void fly() = 0;
};

class Penguin : public Bird {
public:
    void fly() override {
        throw std::runtime_error("Penguins can't fly!");
    }
};

// Good Example - Follows LSP
class Bird {
public:
    virtual void move() = 0;
};

class FlyingBird : public Bird {
public:
    void move() override {
        fly();
    }
    virtual void fly() = 0;
};

class Penguin : public Bird {
public:
    void move() override {
        walk();
    }
    void walk() { /* ... */ }
};
```

## Interface Segregation Principle (ISP)

### Definition
"Clients should not be forced to depend on interfaces they do not use."

### Key Concepts
- Keep interfaces small and focused
- Avoid fat interfaces
- Split large interfaces into smaller ones

### Example
```cpp
// Bad Example - Fat Interface
class Worker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
};

// Good Example - Segregated Interfaces
class Workable {
public:
    virtual void work() = 0;
};

class Eatable {
public:
    virtual void eat() = 0;
};

class Sleepable {
public:
    virtual void sleep() = 0;
};

class Human : public Workable, public Eatable, public Sleepable {
    // Implementation
};
```

## Dependency Inversion Principle (DIP)

### Definition
"High-level modules should not depend on low-level modules. Both should depend on abstractions."

### Key Concepts
- Depend on abstractions, not concrete implementations
- Use dependency injection
- Invert the dependency direction

### Example
```cpp
// Bad Example - Direct Dependency
class EmailService {
public:
    void sendEmail() { /* ... */ }
};

class UserManager {
private:
    EmailService emailService;
public:
    void createUser() {
        // Create user
        emailService.sendEmail();
    }
};

// Good Example - Dependency Inversion
class IEmailService {
public:
    virtual void sendEmail() = 0;
};

class EmailService : public IEmailService {
public:
    void sendEmail() override { /* ... */ }
};

class UserManager {
private:
    IEmailService& emailService;
public:
    UserManager(IEmailService& service) : emailService(service) {}
    void createUser() {
        // Create user
        emailService.sendEmail();
    }
};
```

### Best Practices
1. Use interfaces for dependencies
2. Implement dependency injection
3. Keep high-level modules independent
4. Use abstract factories when needed
5. Consider using a dependency injection container

### Real-World Example
```cpp
// School Management System
class IStaff {
public:
    virtual void performDuties() = 0;
};

class Teacher : public IStaff {
public:
    void performDuties() override {
        // Teaching duties
    }
};

class School {
private:
    std::vector<std::shared_ptr<IStaff>> staff;
public:
    void addStaff(std::shared_ptr<IStaff> member) {
        staff.push_back(member);
    }
    void runSchool() {
        for(auto& member : staff) {
            member->performDuties();
        }
    }
};
```

