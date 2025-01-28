#include "ReportGenerator.h"
#include <fstream>
#include <iostream>
#include <map>

void saveReportToFile(const std::vector<Transaction>& transactions, const std::string& reportFilename) {
    std::ofstream outFile(reportFilename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving reports." << std::endl;
        return;
    }

    outFile << "Transaction Report\n";
    outFile << "Date,Amount,Category,Notes\n";

    for (const auto& transaction : transactions) {
        outFile << transaction.getDate() << ","
            << transaction.getAmount() << ","
            << transaction.getCategory() << ","
            << transaction.getNotes() << "\n";
    }

    outFile.close();
    std::cout << "Report saved to file: " << reportFilename << std::endl;
}

void generateCategorySummary(const std::vector<Transaction>& transactions) {
    std::map<std::string, double> categoryTotals;

    for (const auto& transaction : transactions) {
        categoryTotals[transaction.getCategory()] += transaction.getAmount();
    }

    std::cout << "\nCategory Summary:\n";
    for (const auto& pair : categoryTotals) {
        std::cout << "  " << pair.first << ": $" << pair.second << std::endl;
    }
}
