#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Ingredient {
public:
    string name;
    int quantity;

    Ingredient(string name, int quantity) : name(name), quantity(quantity) {}
};

class Inventory {
private:
    unordered_map<string, int> stock;

public:
    void addIngredient(string name, int qty) {
        stock[name] += qty;
        cout << "Refilled " << qty << " of " << name << endl;
    }

    bool hasIngredients(const unordered_map<string, int>& required) {
        for (auto& item : required) {
            if (stock[item.first] < item.second)
                return false;
        }
        return true;
    }

    void useIngredients(const unordered_map<string, int>& required) {
        for (auto& item : required) {
            stock[item.first] -= item.second;
        }
    }

    void display() {
        cout << "\nInventory Status:\n";
        for (auto& item : stock) {
            cout << item.first << ": " << item.second << endl;
        }
    }
};

class Beverage {
public:
    string name;
    unordered_map<string, int> ingredients;

    Beverage(string name, unordered_map<string, int> ingredients)
        : name(name), ingredients(ingredients) {}
};

class CoffeeMachine {
private:
    Inventory inventory;
    vector<Beverage> menu;

public:
    CoffeeMachine() {
        // prefill some inventory
        inventory.addIngredient("Water", 500);
        inventory.addIngredient("Milk", 300);
        inventory.addIngredient("CoffeePowder", 200);
        inventory.addIngredient("Sugar", 100);
    }

    void addBeverageToMenu(Beverage b) {
        menu.push_back(b);
    }

    void displayMenu() {
        cout << "\nAvailable Beverages:\n";
        for (int i = 0; i < menu.size(); i++) {
            cout << i + 1 << ". " << menu[i].name << endl;
        }
    }

    void makeBeverage(int choice) {
        if (choice < 1 || choice > menu.size()) {
            cout << "Invalid choice.\n";
            return;
        }
        Beverage b = menu[choice - 1];
        if (inventory.hasIngredients(b.ingredients)) {
            inventory.useIngredients(b.ingredients);
            cout << "Serving your " << b.name << ". Enjoy!\n";
        } else {
            cout << "Insufficient ingredients for " << b.name << ".\n";
        }
    }

    void refillIngredient(string name, int qty) {
        inventory.addIngredient(name, qty);
    }

    void showInventory() {
        inventory.display();
    }
};

// --- Main Driver ---
int main() {
    CoffeeMachine machine;

    // Setup beverages
    machine.addBeverageToMenu(Beverage("Espresso", {
        {"Water", 50}, {"CoffeePowder", 20}
    }));
    machine.addBeverageToMenu(Beverage("Cappuccino", {
        {"Water", 50}, {"Milk", 60}, {"CoffeePowder", 20}, {"Sugar", 10}
    }));

    // Simple loop to simulate usage
    int choice;
    do {
        cout << "\n1. Show Menu\n2. Make Beverage\n3. Refill Ingredient\n4. Show Inventory\n5. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            machine.displayMenu();
        } else if (choice == 2) {
            machine.displayMenu();
            cout << "Select beverage number: ";
            int b;
            cin >> b;
            machine.makeBeverage(b);
        } else if (choice == 3) {
            string name;
            int qty;
            cout << "Enter ingredient name: ";
            cin >> name;
            cout << "Enter quantity to refill: ";
            cin >> qty;
            machine.refillIngredient(name, qty);
        } else if (choice == 4) {
            machine.showInventory();
        }
    } while (choice != 5);

    return 0;
}
