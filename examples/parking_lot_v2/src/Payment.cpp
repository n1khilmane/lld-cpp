#include "../include/Payment.hpp"

bool Cash::initiateTransaction() {
    // Simulate cash payment processing
    status = PaymentStatus::COMPLETED;
    return true;
}

bool CreditCard::initiateTransaction() {
    // Simulate credit card payment processing
    status = PaymentStatus::COMPLETED;
    return true;
} 