#ifndef CATEGORY_H
#define CATEGORY_H

// Category.h
// Defines the Category class for organizing transactions in VaultWise.

#include <string>
#include <vector>
#include "Transaction.h"

// The Category class represents a financial category that stores transactions.
class Category {
private:
    std::string name;  // Name of the category (e.g., "Food", "Rent", "Utilities").
    std::vector<Transaction> transactions;  // List of transactions under this category.

public:
    // Constructor: Initializes a Category with a given name.
    Category(const std::string& name);

    // Returns the name of the category.
    std::string getName() const;

    // Adds a transaction to the category.
    void addTransaction(const Transaction& transaction);

    // Retrieves all transactions in this category.
    const std::vector<Transaction>& getTransactions() const;
};

#endif // CATEGORY_H
