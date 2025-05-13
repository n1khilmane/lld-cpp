#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

enum LockerSize { SMALL, MEDIUM, LARGE };
enum LockerState { AVAILABLE, OCCUPIED };

class Locker {
public:
    string id;
    LockerSize size;
    LockerState state;
    string assignedPackageId;

    Locker() {}

    Locker(string _id, LockerSize _size) {
        id = _id;
        size = _size;
        state = AVAILABLE;
        assignedPackageId = "";
    }
};

class Package {
public:
    string packageId;
    LockerSize size;
    string userId;
    time_t deliveryTime;

    Package() {}

    Package(string _packageId, LockerSize _size, string _userId) {
        packageId = _packageId;
        size = _size;
        userId = _userId;
        deliveryTime = time(0);
    }
};

class LockerLocation {
public:
    string locationId;
    vector<Locker> lockers;

    LockerLocation() {}

    LockerLocation(string _locationId) {
        locationId = _locationId;
    }

    void addLocker(Locker locker) {
        lockers.push_back(locker);
    }
};

class User {
public:
    string userId;
    string name;
    string phone;

    User() {}

    User(string _userId, string _name, string _phone) {
        userId = _userId;
        name = _name;
        phone = _phone;
    }
};

class DeliveryAgent {
public:
    string agentId;
    string name;

    DeliveryAgent() {}

    DeliveryAgent(string _agentId, string _name) {
        agentId = _agentId;
        name = _name;
    }

    bool deliverPackage(class LockerService& service, string locationId, Package pkg);
};

class NotificationService {
public:
    void sendPickupCode(string userId, string code) {
        cout << "Pickup code for user " << userId << ": " << code << endl;
    }
};

class LockerService {
private:
    unordered_map<string, LockerLocation> locations;
    unordered_map<string, Package> packageMap;
    unordered_map<string, string> pickupCodeMap;
    NotificationService notifier;

public:
    void addLocation(LockerLocation loc) {
        locations[loc.locationId] = loc;
    }

    bool assignLocker(string locationId, Package pkg) {
        LockerLocation& loc = locations[locationId];

        for (int i = 0; i < loc.lockers.size(); i++) {
            Locker& locker = loc.lockers[i];
            if (locker.size == pkg.size && locker.state == AVAILABLE) {
                locker.state = OCCUPIED;
                locker.assignedPackageId = pkg.packageId;
                packageMap[pkg.packageId] = pkg;

                string pickupCode = "CODE" + pkg.packageId;
                pickupCodeMap[pkg.userId] = pickupCode;
                notifier.sendPickupCode(pkg.userId, pickupCode);
                return true;
            }
        }

        cout << "No available locker found for package " << pkg.packageId << endl;
        return false;
    }

    bool pickupPackage(string userId, string code) {
        if (pickupCodeMap[userId] != code) {
            cout << "Invalid code!" << endl;
            return false;
        }

        string pkgId = code.substr(4); // Strip "CODE"
        for (auto& entry : locations) {
            LockerLocation& loc = entry.second;
            for (Locker& locker : loc.lockers) {
                if (locker.assignedPackageId == pkgId) {
                    locker.state = AVAILABLE;
                    locker.assignedPackageId = "";
                    cout << "Package " << pkgId << " picked up successfully." << endl;
                    return true;
                }
            }
        }

        cout << "Package not found in any locker." << endl;
        return false;
    }

    void checkForExpiredPackages(int expirySeconds) {
        time_t now = time(0);
        for (auto& entry : packageMap) {
            Package& pkg = entry.second;
            if (difftime(now, pkg.deliveryTime) > expirySeconds) {
                cout << "Package " << pkg.packageId << " has expired!" << endl;
            }
        }
    }
};

bool DeliveryAgent::deliverPackage(LockerService& service, string locationId, Package pkg) {
    cout << "Agent " << name << " delivering package " << pkg.packageId << "...\n";
    return service.assignLocker(locationId, pkg);
}

class AuthService {
private:
    unordered_map<string, bool> userLoginStatus;
    unordered_map<string, bool> agentLoginStatus;

public:
    void registerUser(User user) {
        userLoginStatus[user.userId] = false;
        cout << "User " << user.name << " registered.\n";
    }

    void registerAgent(DeliveryAgent agent) {
        agentLoginStatus[agent.agentId] = false;
        cout << "Agent " << agent.name << " registered.\n";
    }

    bool loginUser(string userId) {
        if (userLoginStatus.count(userId)) {
            userLoginStatus[userId] = true;
            cout << "User " << userId << " logged in.\n";
            return true;
        }
        cout << "User not found!\n";
        return false;
    }

    bool loginAgent(string agentId) {
        if (agentLoginStatus.count(agentId)) {
            agentLoginStatus[agentId] = true;
            cout << "Agent " << agentId << " logged in.\n";
            return true;
        }
        cout << "Agent not found!\n";
        return false;
    }

    void logoutUser(string userId) {
        userLoginStatus[userId] = false;
        cout << "User " << userId << " logged out.\n";
    }

    void logoutAgent(string agentId) {
        agentLoginStatus[agentId] = false;
        cout << "Agent " << agentId << " logged out.\n";
    }

    bool isUserLoggedIn(string userId) {
        return userLoginStatus[userId];
    }

    bool isAgentLoggedIn(string agentId) {
        return agentLoginStatus[agentId];
    }
};

int main() {
    LockerService service;
    AuthService auth;

    // Setup locker location
    LockerLocation loc("LOC1");
    loc.addLocker(Locker("L1", SMALL));
    loc.addLocker(Locker("L2", MEDIUM));
    service.addLocation(loc);

    // Create user and agent
    User user("USER1", "Alice", "123-456");
    DeliveryAgent agent("AGENT1", "Bob");

    // Register and login
    auth.registerUser(user);
    auth.registerAgent(agent);
    auth.loginUser("USER1");
    auth.loginAgent("AGENT1");

    // Delivery flow
    Package pkg("PKG1", SMALL, user.userId);
    if (auth.isAgentLoggedIn(agent.agentId)) {
        agent.deliverPackage(service, "LOC1", pkg);
    }

    // Simulate user pickup
    if (auth.isUserLoggedIn(user.userId)) {
        service.pickupPackage(user.userId, "CODEPKG1");
    }

    // Simulate expired package check
    cout << "\n--- Checking for expired packages after delay ---\n";
    service.checkForExpiredPackages(1); // 1 sec expiry window

    return 0;
}
