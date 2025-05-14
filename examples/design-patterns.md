✅ 1. Factory Pattern – for Beverage Creation
Problem:
Creating different types of beverages (Espresso, Cappuccino, Latte, etc.) with their unique ingredients.

Why Factory?
Centralizes the creation logic.

Easy to add new beverages without changing core code.

Keeps CoffeeMachine clean.

How to use:
cpp
Copy
Edit
class BeverageFactory {
public:
    static Beverage createBeverage(const string& type) {
        if (type == "Espresso") {
            return Beverage("Espresso", {
                {"Water", 50}, {"CoffeePowder", 20}
            });
        } else if (type == "Cappuccino") {
            return Beverage("Cappuccino", {
                {"Water", 50}, {"Milk", 60}, {"CoffeePowder", 20}, {"Sugar", 10}
            });
        }
        throw invalid_argument("Unknown beverage type");
    }
};
You now call:

cpp
Copy
Edit
machine.addBeverageToMenu(BeverageFactory::createBeverage("Espresso"));
✅ 2. Singleton Pattern – for CoffeeMachine instance
Problem:
You typically only want one instance of a coffee machine.

Why Singleton?
Ensure one global instance.

Prevent duplicate inventory/state conflicts.

How to use:
cpp
Copy
Edit
class CoffeeMachine {
private:
    static CoffeeMachine* instance;
    CoffeeMachine() {} // private constructor

public:
    static CoffeeMachine* getInstance() {
        if (!instance)
            instance = new CoffeeMachine();
        return instance;
    }
};
CoffeeMachine* CoffeeMachine::instance = nullptr;
Usage:

cpp
Copy
Edit
CoffeeMachine* machine = CoffeeMachine::getInstance();
(For whiteboard rounds, you can skip full implementation but mention intent.)

✅ 3. Strategy Pattern – for Beverage Preparation Logic
Problem:
Each beverage might have a different preparation logic (e.g., adding froth, adjusting brew time).

Why Strategy?
Decouple the makeBeverage() logic.

Easier to test and extend individual strategies.

How to use:
cpp
Copy
Edit
class BeverageStrategy {
public:
    virtual void prepare() = 0;
};

class EspressoStrategy : public BeverageStrategy {
public:
    void prepare() override {
        cout << "Brewing Espresso...\n";
    }
};

class CappuccinoStrategy : public BeverageStrategy {
public:
    void prepare() override {
        cout << "Adding milk froth, brewing Cappuccino...\n";
    }
};
Associate strategy with Beverage:

cpp
Copy
Edit
class Beverage {
public:
    string name;
    unordered_map<string, int> ingredients;
    BeverageStrategy* strategy;

    Beverage(string name, unordered_map<string, int> ing, BeverageStrategy* strat)
        : name(name), ingredients(ing), strategy(strat) {}

    void prepare() {
        strategy->prepare();
    }
};
✅ 4. Observer Pattern – for Low Ingredient Notification (optional extension)
Problem:
Notify admin when ingredient levels fall below threshold.

Why Observer?
Inventory can notify subscribed listeners (e.g., admin dashboard, SMS alert system).

How to use (conceptually):
cpp
Copy
Edit
class Observer {
public:
    virtual void notify(string msg) = 0;
};

class AdminNotifier : public Observer {
public:
    void notify(string msg) override {
        cout << "Admin Alert: " << msg << endl;
    }
};

class Inventory {
    vector<Observer*> observers;
    void notifyLowStock(string item) {
        for (auto obs : observers) {
            obs->notify("Low stock: " + item);
        }
    }
};
🚀 Summary Table
Pattern	Use Case	Why it Fits
Factory	Create different Beverage types	Clean, scalable object creation
Singleton	Ensure one instance of CoffeeMachine	Global control, shared state
Strategy	Different beverage preparation styles	Decouples behavior
Observer	Notify admin on low ingredients	Reactive design pattern