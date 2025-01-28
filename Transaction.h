#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string date;
    double amount;
    std::string category;
    std::string notes;

public:
    Transaction();
    Transaction(const std::string& date, double amount, const std::string& category, const std::string& notes);

    std::string getDate() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getNotes() const;
};

#endif // TRANSACTION_H
