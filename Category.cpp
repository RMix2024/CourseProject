// Category.cpp
// Implements the Category class for organizing transactions.

#include "Category.h"

// Constructor: Initializes a Category with the given name.
Category::Category(const std::string& name) : name(name) {}

// Returns the name of the category.
std::string Category::getName() const {
    return name;
}

// Adds a transaction to this category.
void Category::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

// Retrieves all transactions in this category.
const std::vector<Transaction>& Category::getTransactions() const {
    return transactions;
}
