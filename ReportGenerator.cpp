// ReportGenerator.cpp
// Implements functions for generating and saving transaction reports.

#include "ReportGenerator.h"
#include <fstream>   // For file handling
#include <iostream>  // For console output
#include <map>       // For category-wise total calculation

// Saves transaction details into a CSV report file.
// Creates a new file if it doesn't exist.
void saveReportToFile(const std::vector<Transaction>& transactions, const std::string& reportFilename) {
    std::ofstream outFile(reportFilename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving reports." << std::endl;
        return;
    }

    // Write CSV header
    outFile << "Transaction Report\n";
    outFile << "Date,Amount,Category,Notes\n";

    // Write transaction details
    for (const auto& transaction : transactions) {
        outFile << transaction.getDate() << ","
            << transaction.getAmount() << ","
            << transaction.getCategory() << ","
            << transaction.getNotes() << "\n";
    }

    outFile.close();
    std::cout << "Report saved to file: " << reportFilename << std::endl;
}

// Generates and displays a summary of total spending per category.
void generateCategorySummary(const std::vector<Transaction>& transactions) {
    std::map<std::string, double> categoryTotals;  // Stores category-wise total spending

    // Calculate totals per category
    for (const auto& transaction : transactions) {
        categoryTotals[transaction.getCategory()] += transaction.getAmount();
    }

    // Display category summary
    std::cout << "\nCategory Summary:\n";
    for (const auto& pair : categoryTotals) {
        std::cout << "  " << pair.first << ": $" << pair.second << std::endl;
    }
}
