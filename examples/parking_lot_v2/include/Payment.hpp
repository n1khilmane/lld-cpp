#pragma once
#include "Types.hpp"
#include <ctime>

class Payment {
protected:
    double amount;
    PaymentStatus status;
    time_t timestamp;

public:
    Payment(double amt) : amount(amt), status(PaymentStatus::PENDING), timestamp(time(nullptr)) {}
    virtual ~Payment() = default;

    double getAmount() const { return amount; }
    PaymentStatus getStatus() const { return status; }
    time_t getTimestamp() const { return timestamp; }

    virtual bool initiateTransaction() = 0;
};

class Cash : public Payment {
public:
    Cash(double amt) : Payment(amt) {}
    bool initiateTransaction() override;
};

class CreditCard : public Payment {
private:
    std::string cardNumber;
    std::string cardHolderName;
    std::string expiryDate;

public:
    CreditCard(double amt, const std::string& cardNo, 
               const std::string& holderName, const std::string& expiry)
        : Payment(amt), cardNumber(cardNo), cardHolderName(holderName), expiryDate(expiry) {}

    bool initiateTransaction() override;
}; 