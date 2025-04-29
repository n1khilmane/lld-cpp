#pragma once
#include "Types.hpp"
#include <string>

class ParkingSpot;
class DisplayBoard;
class Entrance;
class Exit;

class Account {
protected:
    std::string userName;
    std::string password;
    Person person;
    AccountStatus status;

public:
    Account(const std::string& user, const std::string& pass, const Person& p)
        : userName(user), password(pass), person(p), status(AccountStatus::ACTIVE) {}
    virtual ~Account() = default;

    std::string getUserName() const { return userName; }
    AccountStatus getStatus() const { return status; }
    void setStatus(AccountStatus newStatus) { status = newStatus; }

    virtual bool resetPassword() = 0;
};

class Admin : public Account {
public:
    Admin(const std::string& user, const std::string& pass, const Person& p)
        : Account(user, pass, p) {}

    bool addParkingSpot(std::shared_ptr<ParkingSpot> spot);
    bool addDisplayBoard(std::shared_ptr<DisplayBoard> displayBoard);
    bool addEntrance(std::shared_ptr<Entrance> entrance);
    bool addExit(std::shared_ptr<Exit> exit);
    bool resetPassword() override;
};

class ParkingAttendant : public Account {
public:
    ParkingAttendant(const std::string& user, const std::string& pass, const Person& p)
        : Account(user, pass, p) {}

    bool processTicket(const std::string& ticketNumber);
    bool resetPassword() override;
}; 