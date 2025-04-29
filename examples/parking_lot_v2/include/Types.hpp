#pragma once
#include <string>

enum class PaymentStatus {
    COMPLETED,
    FAILED,
    PENDING,
    UNPAID,
    REFUNDED
};

enum class AccountStatus {
    ACTIVE,
    CLOSED,
    CANCELED,
    BLACKLISTED,
    NONE
};

class Address {
private:
    int zipCode;
    std::string address;
    std::string city;
    std::string state;
    std::string country;

public:
    Address(int zip, const std::string& addr, const std::string& cty, 
            const std::string& st, const std::string& cntry)
        : zipCode(zip), address(addr), city(cty), state(st), country(cntry) {}

    int getZipCode() const { return zipCode; }
    std::string getAddress() const { return address; }
    std::string getCity() const { return city; }
    std::string getState() const { return state; }
    std::string getCountry() const { return country; }
};

class Person {
private:
    std::string name;
    std::string address;
    std::string phone;
    std::string email;

public:
    Person(const std::string& n, const std::string& addr, 
           const std::string& ph, const std::string& em)
        : name(n), address(addr), phone(ph), email(em) {}

    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getPhone() const { return phone; }
    std::string getEmail() const { return email; }
}; 