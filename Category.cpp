#include "Category.h"

Category::Category(const std::string& name) : name(name) {}

std::string Category::getName() const {
    return name;
}

void Category::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

const std::vector<Transaction>& Category::getTransactions() const {
    return transactions;
}
