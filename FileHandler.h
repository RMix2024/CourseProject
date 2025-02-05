#ifndef FILEHANDLER_H
#define FILEHANDLER_H

// FileHandler.h
// Handles file operations for saving, loading, and deleting transactions.

#include <vector>
#include "Transaction.h"

// Saves all transactions to a CSV file.
void saveTransactionsToFile(const std::vector<Transaction>& transactions, const std::string& filename);

// Loads transactions from a CSV file.
void loadTransactionsFromFile(std::vector<Transaction>& transactions, const std::string& filename);

// Deletes the transaction file from the system.
void deleteTransactionFile(const std::string& filename);

#endif // FILEHANDLER_H
