// FileHandler.cpp
// Implements file handling functions for transaction storage.

#include "FileHandler.h"
#include <fstream>   // For file handling
#include <sstream>   // For string stream processing
#include <iostream>  // For console output
#include <cstdio>    // For std::remove (deleting files)

// Saves all transactions to a CSV file.
// If the file does not exist, it will be created.
void saveTransactionsToFile(const std::vector<Transaction>& transactions, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving transactions." << std::endl;
        return;
    }

    // Write CSV header
    outFile << "Date,Amount,Category,Notes\n";

    // Write transactions to file
    for (const auto& transaction : transactions) {
        outFile << transaction.getDate() << ","
            << transaction.getAmount() << ","
            << transaction.getCategory() << ","
            << transaction.getNotes() << "\n";
    }

    std::cout << "Transactions successfully saved to '" << filename << "'." << std::endl;
}

// Loads transactions from a CSV file.
// If the file does not exist, this function safely exits without errors.
void loadTransactionsFromFile(std::vector<Transaction>& transactions, const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Warning: Could not open '" << filename << "'. No transactions loaded." << std::endl;
        return;
    }

    std::string line;
    std::getline(inFile, line); // Skip CSV header

    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string date, category, notes;
        double amount;

        std::getline(ss, date, ',');  // Read date
        ss >> amount;                 // Read amount
        ss.ignore();                   // Ignore comma separator
        std::getline(ss, category, ',');  // Read category
        std::getline(ss, notes);       // Read notes

        // Add transaction to the list
        transactions.emplace_back(date, amount, category, notes);
    }

    std::cout << "Transactions loaded from '" << filename << "'." << std::endl;
}

// Deletes the transaction file if it exists.
// Displays success or error messages.
void deleteTransactionFile(const std::string& filename) {
    if (std::remove(filename.c_str()) == 0) {
        std::cout << "Transaction file '" << filename << "' deleted successfully." << std::endl;
    }
    else {
        std::cerr << "Error: Could not delete the file '" << filename << "'." << std::endl;
    }
}
