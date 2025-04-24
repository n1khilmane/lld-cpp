# Object-Oriented Programming in C++

## Table of Contents
1. [Encapsulation](#encapsulation)
2. [Abstraction](#abstraction)
3. [Inheritance](#inheritance)
4. [Polymorphism](#polymorphism)
5. [Operator Overloading](#operator-overloading)

## Encapsulation

### Definition
Encapsulation is a fundamental programming technique used to achieve data hiding in OOP. It refers to binding data and the methods to manipulate that data together in a single unit—class.

### Key Concepts
- Data hiding: Masking a class's internal operations
- Interface: Providing controlled access to class members
- Getters and Setters: Public methods to access private data

### Example
```cpp
class BankAccount {
private:
    double balance;  // Private data member

public:
    // Public interface
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    double getBalance() {
        return balance;
    }
};
```

## Abstraction

### Definition
Abstraction is a technique that simplifies program structure by hiding irrelevant details and showing only essential features.

### Real-World Examples
1. TV Remote Control
   - User only needs to know which button to press
   - Internal circuitry details are hidden

2. Car Operation
   - Driver only needs to know how to use pedals and steering
   - Engine mechanics are abstracted away

### Advantages
- Reduces system complexity
- Improves code reusability
- Enhances maintainability
- Refines modularity

## Inheritance

### Definition
Inheritance allows creating a new class from an existing class, inheriting its properties and methods.

### Types of Inheritance
1. Single Inheritance
   - One base class, one derived class
2. Multiple Inheritance
   - Multiple base classes, one derived class
3. Multilevel Inheritance
   - Base class → Derived class → Further derived class
4. Hierarchical Inheritance
   - One base class, multiple derived classes
5. Hybrid Inheritance
   - Combination of multiple inheritance types

### Access Modifiers
- Public: Accessible everywhere
- Protected: Accessible in derived classes
- Private: Accessible only within the class

### Example
```cpp
class Animal {
protected:
    string name;
public:
    virtual void makeSound() = 0;
};

class Dog : public Animal {
public:
    void makeSound() override {
        cout << "Woof!" << endl;
    }
};
```

## Polymorphism

### Definition
Polymorphism allows objects to have multiple forms and behaviors. The word comes from Greek: "poly" (many) and "morph" (forms).

### Types of Polymorphism

#### 1. Dynamic Polymorphism (Runtime)
- Achieved through method overriding
- Resolved at runtime
- Uses virtual functions

Example:
```cpp
class Shape {
public:
    virtual double getArea() = 0;
};

class Circle : public Shape {
public:
    double getArea() override {
        return 3.14 * radius * radius;
    }
};
```

#### 2. Static Polymorphism (Compile-time)
- Achieved through method overloading
- Resolved at compile time
- Uses function overloading

Example:
```cpp
class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
    
    double add(double a, double b) {
        return a + b;
    }
};
```

## Operator Overloading

### Definition
Operator overloading allows operators to work with user-defined types in a specific way.

### Example
```cpp
class Complex {
private:
    double real, imag;
public:
    Complex operator+(const Complex& other) {
        Complex result;
        result.real = real + other.real;
        result.imag = imag + other.imag;
        return result;
    }
};
```

### Common Overloadable Operators
- Arithmetic: +, -, *, /
- Comparison: ==, !=, <, >
- Assignment: =, +=, -=
- Stream: <<, >>

### Best Practices
1. Maintain operator semantics
2. Return appropriate types
3. Consider const correctness
4. Handle edge cases
5. Document behavior clearly