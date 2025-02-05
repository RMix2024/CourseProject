// Transaction.cpp
// Implements the Transaction class for storing financial records.

#include "Transaction.h"

// Default constructor: Initializes an empty transaction.
Transaction::Transaction() : date(""), amount(0.0), category(""), notes("") {}

// Parameterized constructor: Initializes a transaction with specific details.
Transaction::Transaction(const std::string& date, double amount, const std::string& category, const std::string& notes)
    : date(date), amount(amount), category(category), notes(notes) {
}

// Returns the date of the transaction.
std::string Transaction::getDate() const { return date; }

// Returns the amount of the transaction.
double Transaction::getAmount() const { return amount; }

// Returns the category of the transaction.
std::string Transaction::getCategory() const { return category; }

// Returns any notes associated with the transaction.
std::string Transaction::getNotes() const { return notes; }
