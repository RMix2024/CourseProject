#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include "Transaction.h"

class Category {
private:
    std::string name;
    std::vector<Transaction> transactions;

public:
    Category(const std::string& name);

    std::string getName() const;
    void addTransaction(const Transaction& transaction);
    const std::vector<Transaction>& getTransactions() const;
};

#endif // CATEGORY_H
