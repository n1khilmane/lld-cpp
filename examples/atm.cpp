#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// -------------------- Entities ---------------------
class Account {
    int id;
    double balance;

public:
    Account(int id, double balance) : id(id), balance(balance) {}
    int getId() const { return id; }

    double getBalance() const { return balance; }

    bool debit(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    void credit(double amount) {
        balance += amount;
    }
};

class Card {
    string cardNumber;
    string pin;
    vector<Account> accounts;

public:
    Card(string number, string pin, vector<Account> accts) :
        cardNumber(number), pin(pin), accounts(accts) {}

    string getCardNumber() const { return cardNumber; }

    bool validatePIN(string enteredPIN) const {
        return enteredPIN == pin;
    }

    vector<Account>& getAccounts() { return accounts; }
};

// -------------------- Hardware ---------------------
class CardReader {
public:
    Card readCard() {
        cout << "Reading card...\n";
        return Card("1234", "4321", {Account(1, 1000), Account(2, 5000)});
    }
};

class Keypad {
public:
    string getPIN() {
        cout << "Enter PIN: ";
        string pin;
        cin >> pin;
        return pin;
    }

    double getAmount() {
        cout << "Enter amount: ";
        double amt;
        cin >> amt;
        return amt;
    }
};

class Screen {
public:
    void showMessage(const string& msg) {
        cout << msg << endl;
    }

    void showBalance(double balance) {
        cout << "Balance: $" << balance << endl;
    }
};

class CashDispenser {
public:
    void dispenseCash(double amount) {
        cout << "Dispensing $" << amount << endl;
    }
};

// -------------------- Backend ---------------------
class BankServer {
public:
    bool verifyPIN(const Card& card, const string& enteredPIN) {
        return card.validatePIN(enteredPIN);
    }

    bool withdraw(Account& account, double amount) {
        return account.debit(amount);
    }

    void deposit(Account& account, double amount) {
        account.credit(amount);
    }

    double getBalance(const Account& account) {
        return account.getBalance();
    }
};

// -------------------- Orchestrator ---------------------
class ATM {
    CardReader reader;
    Keypad keypad;
    Screen screen;
    CashDispenser dispenser;
    BankServer server;

public:
    void start() {
        screen.showMessage("Welcome to ATM");
        Card card = reader.readCard();
        string pin = keypad.getPIN();

        if (!server.verifyPIN(card, pin)) {
            screen.showMessage("Invalid PIN. Exiting.");
            return;
        }

        screen.showMessage("Authentication successful.");
        vector<Account>& accounts = card.getAccounts();

        screen.showMessage("Select Account [0: Savings, 1: Checking]");
        int choice;
        cin >> choice;

        if (choice >= accounts.size()) {
            screen.showMessage("Invalid account selection.");
            return;
        }

        Account& selectedAccount = accounts[choice];

        screen.showMessage("Choose Operation: 1. Withdraw  2. Deposit  3. Balance");
        int option;
        cin >> option;

        if (option == 1) {
            double amt = keypad.getAmount();
            if (server.withdraw(selectedAccount, amt)) {
                dispenser.dispenseCash(amt);
                screen.showMessage("Withdraw successful.");
            } else {
                screen.showMessage("Insufficient balance.");
            }
        } else if (option == 2) {
            double amt = keypad.getAmount();
            server.deposit(selectedAccount, amt);
            screen.showMessage("Deposit successful.");
        } else if (option == 3) {
            double bal = server.getBalance(selectedAccount);
            screen.showBalance(bal);
        } else {
            screen.showMessage("Invalid option.");
        }

        screen.showMessage("Thank you for using ATM.");
    }
};

// -------------------- Main ---------------------
int main() {
    ATM atm;
    atm.start();
    return 0;
}
