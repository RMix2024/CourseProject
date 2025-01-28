#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio> // For std::remove

void saveTransactionsToFile(const std::vector<Transaction>& transactions, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving transactions." << std::endl;
        return;
    }

    outFile << "Date,Amount,Category,Notes\n";
    for (const auto& transaction : transactions) {
        outFile << transaction.getDate() << ","
            << transaction.getAmount() << ","
            << transaction.getCategory() << ","
            << transaction.getNotes() << "\n";
    }
}

void loadTransactionsFromFile(std::vector<Transaction>& transactions, const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        return; // File might not exist yet
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string date, category, notes;
        double amount;

        std::getline(ss, date, ',');
        ss >> amount;
        ss.ignore();
        std::getline(ss, category, ',');
        std::getline(ss, notes);

        transactions.emplace_back(date, amount, category, notes);
    }
}

void deleteTransactionFile(const std::string& filename) {
    if (std::remove(filename.c_str()) == 0) {
        std::cout << "Transaction file '" << filename << "' deleted successfully." << std::endl;
    }
    else {
        std::cerr << "Error: Could not delete the file '" << filename << "'." << std::endl;
    }
}
