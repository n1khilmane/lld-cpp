# Design Patterns in C++

## Table of Contents
1. [Creational Patterns](#creational-patterns)
2. [Structural Patterns](#structural-patterns)
3. [Behavioral Patterns](#behavioral-patterns)

## Creational Patterns

### Introduction
Creational design patterns deal with object creation mechanisms, providing optimized object creation techniques and helping to control object creation.

### Factory Pattern
#### Definition
Provides a template for creating objects without specifying the exact class of object that will be created.

#### Example
```cpp
class Product {
public:
    virtual void operation() = 0;
};

class ConcreteProductA : public Product {
public:
    void operation() override {
        std::cout << "Product A operation" << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    void operation() override {
        std::cout << "Product B operation" << std::endl;
    }
};

class Factory {
public:
    static std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "A") {
            return std::make_unique<ConcreteProductA>();
        } else if (type == "B") {
            return std::make_unique<ConcreteProductB>();
        }
        return nullptr;
    }
};
```

### Singleton Pattern
#### Definition
Ensures a class has only one instance and provides a global point of access to it.

#### Example
```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {} // Private constructor

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
    
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

Singleton* Singleton::instance = nullptr;
```

### Builder Pattern
#### Definition
Separates the construction of a complex object from its representation.

#### Example
```cpp
class Computer {
private:
    std::string cpu;
    std::string ram;
    std::string storage;

public:
    class Builder {
    private:
        Computer* computer;
    public:
        Builder() : computer(new Computer()) {}
        
        Builder& setCPU(const std::string& cpu) {
            computer->cpu = cpu;
            return *this;
        }
        
        Builder& setRAM(const std::string& ram) {
            computer->ram = ram;
            return *this;
        }
        
        Builder& setStorage(const std::string& storage) {
            computer->storage = storage;
            return *this;
        }
        
        Computer* build() {
            return computer;
        }
    };
};
```

## Structural Patterns

### Introduction
Structural patterns are concerned with object relationships and the structure of classes or objects.

### Decorator Pattern
#### Definition
Attaches additional responsibilities to an object dynamically.

#### Example
```cpp
class Component {
public:
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "Basic operation" << std::endl;
    }
};

class Decorator : public Component {
protected:
    Component* component;
public:
    Decorator(Component* c) : component(c) {}
    void operation() override {
        component->operation();
    }
};

class ConcreteDecorator : public Decorator {
public:
    ConcreteDecorator(Component* c) : Decorator(c) {}
    void operation() override {
        Decorator::operation();
        std::cout << "Additional operation" << std::endl;
    }
};
```

### Adapter Pattern
#### Definition
Allows incompatible interfaces to work together.

#### Example
```cpp
class OldInterface {
public:
    virtual void oldMethod() = 0;
};

class NewInterface {
public:
    virtual void newMethod() = 0;
};

class Adapter : public NewInterface {
private:
    OldInterface* oldInterface;
public:
    Adapter(OldInterface* old) : oldInterface(old) {}
    void newMethod() override {
        oldInterface->oldMethod();
    }
};
```

### Facade Pattern
#### Definition
Provides a simplified interface to a complex subsystem.

#### Example
```cpp
class SubsystemA {
public:
    void operationA() { /* ... */ }
};

class SubsystemB {
public:
    void operationB() { /* ... */ }
};

class Facade {
private:
    SubsystemA* subsystemA;
    SubsystemB* subsystemB;
public:
    Facade() {
        subsystemA = new SubsystemA();
        subsystemB = new SubsystemB();
    }
    
    void operation() {
        subsystemA->operationA();
        subsystemB->operationB();
    }
};
```

## Behavioral Patterns

### Introduction
Behavioral patterns focus on communication between objects and assignment of responsibilities.

### Observer Pattern
#### Definition
Defines a one-to-many dependency between objects so that when one object changes state, all its dependents are notified.

#### Example
```cpp
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    
    void notify(const std::string& message) {
        for (auto observer : observers) {
            observer->update(message);
        }
    }
};

class ConcreteObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Received: " << message << std::endl;
    }
};
```

### Command Pattern
#### Definition
Encapsulates a request as an object, thereby letting you parameterize clients with different requests.

#### Example
```cpp
class Command {
public:
    virtual void execute() = 0;
};

class ConcreteCommand : public Command {
private:
    Receiver* receiver;
public:
    ConcreteCommand(Receiver* r) : receiver(r) {}
    void execute() override {
        receiver->action();
    }
};

class Invoker {
private:
    Command* command;
public:
    void setCommand(Command* cmd) {
        command = cmd;
    }
    void executeCommand() {
        command->execute();
    }
};
```

### Strategy Pattern
#### Definition
Defines a family of algorithms, encapsulates each one, and makes them interchangeable.

#### Example
```cpp
class Strategy {
public:
    virtual void algorithm() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void algorithm() override {
        std::cout << "Strategy A" << std::endl;
    }
};

class Context {
private:
    Strategy* strategy;
public:
    void setStrategy(Strategy* s) {
        strategy = s;
    }
    void executeStrategy() {
        strategy->algorithm();
    }
};
```

### Best Practices
1. Choose patterns based on the problem, not the other way around
2. Keep implementations simple and focused
3. Document pattern usage and rationale
4. Consider performance implications
5. Use patterns to improve code maintainability

### Common Pitfalls
1. Over-engineering with unnecessary patterns
2. Not understanding pattern intent
3. Implementing patterns incorrectly
4. Ignoring language-specific features
5. Not considering maintenance costs


