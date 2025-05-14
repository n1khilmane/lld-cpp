#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// ---------------- Menu Item ----------------
class MenuItem {
public:
    string name;
    double price;

    MenuItem(string name, double price) : name(name), price(price) {}
};

// ---------------- Menu ----------------
class Menu {
public:
    vector<MenuItem> items;

    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    void removeItem(string itemName) {
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].name == itemName) {
                items.erase(items.begin() + i);
                break;
            }
        }
    }

    void displayMenu() const {
        cout << "Menu:\n";
        for (int i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i].name << " - $" << items[i].price << "\n";
        }
    }

    MenuItem getItem(int index) const {
        return items[index];
    }
};

// ---------------- Table ----------------
class Table {
public:
    int tableId;
    bool isReserved;

    Table(int id) : tableId(id), isReserved(false) {}

    void reserve() {
        isReserved = true;
    }

    void release() {
        isReserved = false;
    }
};

// ---------------- Order ----------------
class Order {
public:
    int orderId;
    int tableId;
    vector<MenuItem> orderedItems;

    Order(int id, int tableId) : orderId(id), tableId(tableId) {}

    void addItem(const MenuItem& item) {
        orderedItems.push_back(item);
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : orderedItems) {
            total += item.price;
        }
        return total;
    }

    void showOrder() const {
        cout << "Order #" << orderId << " for Table " << tableId << ":\n";
        for (const auto& item : orderedItems) {
            cout << "- " << item.name << " ($" << item.price << ")\n";
        }
    }
};

// ---------------- Bill ----------------
class Bill {
public:
    int billId;
    int orderId;
    double amount;

    Bill(int id, int orderId, double amt) : billId(id), orderId(orderId), amount(amt) {}

    void printBill() const {
        cout << "Bill #" << billId << " for Order #" << orderId << ": Total = $" << amount << "\n";
    }
};

// ---------------- Waiter ----------------
class Waiter {
public:
    string name;
    int waiterId;

    Waiter(int id, string name) : waiterId(id), name(name) {}

    void takeOrder(Order& order, const vector<int>& itemIndices, const Menu& menu) {
        for (int idx : itemIndices) {
            order.addItem(menu.getItem(idx));
        }
    }
};

// ---------------- Customer ----------------
class Customer {
public:
    string name;

    Customer(string name) : name(name) {}

    void placeOrder(Waiter& waiter, Order& order, const vector<int>& itemIndices, const Menu& menu) {
        waiter.takeOrder(order, itemIndices, menu);
    }
};

// ---------------- Restaurant Manager ----------------
class RestaurantManager {
private:
    Menu menu;
    vector<Table> tables;
    vector<Waiter> waiters;
    vector<Order> orders;
    vector<Bill> bills;
    int nextOrderId = 1;
    int nextBillId = 1;

public:
    RestaurantManager(int tableCount) {
        for (int i = 1; i <= tableCount; ++i) {
            tables.push_back(Table(i));
        }
    }

    Menu& getMenu() {
        return menu;
    }

    void addWaiter(const Waiter& w) {
        waiters.push_back(w);
    }

    void showAvailableTables() const {
        cout << "Available Tables: ";
        for (const auto& t : tables) {
            if (!t.isReserved)
                cout << t.tableId << " ";
        }
        cout << "\n";
    }

    Table& getTable(int id) {
        return tables[id - 1];  // assume tableId starts from 1
    }

    Order& createOrder(int tableId) {
        orders.push_back(Order(nextOrderId, tableId));
        return orders.back();
    }

    Bill& generateBill(const Order& order) {
        bills.push_back(Bill(nextBillId++, order.orderId, order.calculateTotal()));
        return bills.back();
    }

    void showAllOrders() const {
        for (const auto& o : orders) {
            o.showOrder();
        }
    }

    void showAllBills() const {
        for (const auto& b : bills) {
            b.printBill();
        }
    }
};

// ---------------- Main Simulation ----------------
int main() {
    RestaurantManager manager(5); // 5 tables
    manager.getMenu().addItem(MenuItem("Burger", 8.0));
    manager.getMenu().addItem(MenuItem("Fries", 3.0));
    manager.getMenu().addItem(MenuItem("Coke", 2.0));

    manager.addWaiter(Waiter(1, "Alice"));
    manager.addWaiter(Waiter(2, "Bob"));

    // Simulate customer flow
    manager.showAvailableTables();
    Table& t1 = manager.getTable(1);
    t1.reserve();

    Customer c1("John");
    Waiter& w1 = manager.getTable(1).isReserved ? manager.getTable(1).tableId % 2 == 0 ? manager.waiters[1] : manager.waiters[0] : manager.waiters[0];

    manager.getMenu().displayMenu();

    Order& o1 = manager.createOrder(t1.tableId);
    vector<int> items = {0, 2}; // Burger, Coke
    c1.placeOrder(w1, o1, items, manager.getMenu());

    o1.showOrder();

    Bill& b1 = manager.generateBill(o1);
    b1.printBill();

    t1.release();

    // Manager summary
    manager.showAllOrders();
    manager.showAllBills();

    return 0;
}
