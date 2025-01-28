#include "Transaction.h"

Transaction::Transaction() : date(""), amount(0.0), category(""), notes("") {}

Transaction::Transaction(const std::string& date, double amount, const std::string& category, const std::string& notes)
    : date(date), amount(amount), category(category), notes(notes) {
}

std::string Transaction::getDate() const { return date; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getCategory() const { return category; }
std::string Transaction::getNotes() const { return notes; }
