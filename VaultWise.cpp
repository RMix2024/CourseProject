#include <iostream>
#include <vector>
#include "Transaction.h"
#include "FileHandler.h"
#include "ReportGenerator.h"
#include <ctime>
#include <sstream>
#include <limits>
#include <cctype> // For std::toupper
#include <iomanip> // Required for std::put_time


void showMainMenu() {
    std::cout << "\nMain Menu:" << std::endl;
    std::cout << "1. Add Transaction" << std::endl;
    std::cout << "2. View Transactions" << std::endl;
    std::cout << "3. Generate Reports" << std::endl;
    std::cout << "4. Delete" << std::endl;
    std::cout << "5. Clear All Transactions" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void handleViewTransactions(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions available." << std::endl;
        return;
    }

    std::cout << "\nTransactions:\n";
    for (size_t i = 0; i < transactions.size(); ++i) {
        const auto& t = transactions[i];
        std::cout << i + 1 << ". Date: " << t.getDate()
            << ", Amount: $" << t.getAmount()
            << ", Category: " << t.getCategory()
            << ", Notes: " << t.getNotes() << std::endl;
    }
}

void handleGenerateReports(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions to generate reports." << std::endl;
        return;
    }

    std::string reportFile = "report.csv";
    saveReportToFile(transactions, reportFile);
    std::cout << "Report generated successfully: " << reportFile << std::endl;
}


void handleDeleteTransaction(std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions available to delete." << std::endl;
        return;
    }

    std::cout << "\nTransactions:" << std::endl;
    for (size_t i = 0; i < transactions.size(); ++i) {
        std::cout << i + 1 << ". " << transactions[i].getDate() << ", "
            << transactions[i].getAmount() << ", "
            << transactions[i].getCategory() << ", "
            << transactions[i].getNotes() << std::endl;
    }

    size_t index;
    std::cout << "\nEnter the number of the transaction to delete: ";
    std::cin >> index;

    if (index < 1 || index > transactions.size()) {
        std::cout << "Invalid choice. No transaction deleted." << std::endl;
        return;
    }

    transactions.erase(transactions.begin() + index - 1);
    std::cout << "Transaction deleted successfully." << std::endl;
}

void handleDelete(std::vector<Transaction>& transactions, const std::string& filename) {
    int choice;
    std::cout << "\nWhat would you like to delete?" << std::endl;
    std::cout << "1. A specific transaction" << std::endl;
    std::cout << "2. The entire transaction file" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        handleDeleteTransaction(transactions);
    }
    else if (choice == 2) {
        deleteTransactionFile(filename);
    }
    else {
        std::cout << "Invalid choice. Returning to main menu." << std::endl;
    }
}

void handleClearAllTransactions(std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions to clear." << std::endl;
        return;
    }

    char confirm;
    std::cout << "Are you sure you want to clear all transactions? (y/n): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        transactions.clear();
        std::cout << "All transactions have been cleared." << std::endl;
    }
    else {
        std::cout << "Clear operation canceled." << std::endl;
    }
}


void handleAddTransaction(std::vector<Transaction>& transactions) {
    std::string date, category, notes;
    double amount;

    // Get the current system date
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    std::ostringstream oss;
    oss << std::put_time(&now, "%Y-%m-%d");
    std::string currentDate = oss.str();

    // Get user input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::cout << "Enter transaction date (YYYY-MM-DD) [default: " << currentDate << "]: ";
    std::getline(std::cin, date);

    if (date.empty()) {
        date = currentDate; // Default to today's date
    }

    std::cout << "Enter transaction amount: ";
    std::cin >> amount;
    std::cin.ignore(); // Clear input buffer after numeric input

    std::cout << "Enter transaction category: ";
    std::getline(std::cin, category);

    // Capitalize the first letter of the category
    if (!category.empty()) {
        category[0] = std::toupper(category[0]);
    }

    std::cout << "Enter transaction notes: ";
    std::getline(std::cin, notes);

    // Add the transaction to the list
    transactions.emplace_back(date, amount, category, notes);
    std::cout << "Transaction added successfully!" << std::endl;
}

int main() {
    std::vector<Transaction> transactions;
    std::string filename = "transactions.csv";

    // Load transactions from file
    loadTransactionsFromFile(transactions, filename);

    int choice;
    do {
        showMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            handleAddTransaction(transactions);
            break;
        case 2:
            handleViewTransactions(transactions);
            break;
        case 3:
            handleGenerateReports(transactions);
            break;
        case 4:
            handleDelete(transactions, filename);
            break;
        case 5:
            handleClearAllTransactions(transactions);
            break;
        case 6:
            std::cout << "Exiting VaultWise. Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    // Save transactions to file
    saveTransactionsToFile(transactions, filename);

    return 0;
}
