#ifndef TRANSACTION_H
#define TRANSACTION_H

// Transaction.h
// Defines the Transaction class for storing individual financial records.

#include <string>

// The Transaction class represents a single financial transaction.
class Transaction {
private:
    std::string date;      // Date of the transaction (YYYY-MM-DD).
    double amount;         // Amount spent or received.
    std::string category;  // Category of the transaction (e.g., "Food", "Rent").
    std::string notes;     // Optional notes related to the transaction.

public:
    // Default constructor: Initializes an empty transaction.
    Transaction();

    // Parameterized constructor: Initializes a transaction with specific details.
    Transaction(const std::string& date, double amount, const std::string& category, const std::string& notes);

    // Returns the date of the transaction.
    std::string getDate() const;

    // Returns the amount of the transaction.
    double getAmount() const;

    // Returns the category of the transaction.
    std::string getCategory() const;

    // Returns any notes associated with the transaction.
    std::string getNotes() const;
};

#endif // TRANSACTION_H
