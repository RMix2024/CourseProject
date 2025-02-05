
 /*   VaultWise - Personal Finance Tracker
    -------------------------------------
    Allows users to record financial transactions
    Supports filtering, reporting, and data persistence via CSV
    Designed for easy expansion (GUI, database integration)*/


#include <iostream>
#include <vector>
#include "Transaction.h"
#include "FileHandler.h"
#include "ReportGenerator.h"
#include <ctime>
#include <sstream>
#include <limits>  // Required for clearing input buffer
#include <cctype> // For std::toupper
#include <iomanip> 
#include <fstream>  // Required for file handling
#include <set>      // Required for std::set
#include <string>   // Required for std::string
#include <algorithm>  // Required for std::transform


 //Displays the main menu to the user.
 
void showMainMenu() {
    std::cout << "\n==============================\n";
    std::cout << "       VAULTWISE MENU         \n";
    std::cout << "==============================\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. View Transactions\n";
    std::cout << "3. Generate Reports\n";
    std::cout << "4. Delete\n";
    std::cout << "5. Clear All Transactions\n";
    std::cout << "6. Exit\n";
    std::cout << "==============================\n";
    std::cout << "Enter your choice: ";
}


 //Displays a list of transactions in a formatted table.
 //Allows users to filter by category.
 

void handleViewTransactions(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions available.\n";
        return;
    }

    // Extract unique categories for filtering (case-insensitive)
    std::set<std::string> uniqueCategories;
    for (const auto& t : transactions) {
        std::string category = t.getCategory();
        std::transform(category.begin(), category.end(), category.begin(), ::tolower); // Convert to lowercase
        uniqueCategories.insert(category);
    }

    // Display available categories
    std::cout << "\nAvailable Categories:\n";
    for (const auto& category : uniqueCategories) {
        std::cout << " - " << category << std::endl;
    }

    // Ask user for category filter
    std::string filterCategory;
    std::cout << "\nEnter category to filter transactions (or leave blank for all): ";
    std::getline(std::cin, filterCategory);

    // Convert user input to lowercase to match stored categories
    std::transform(filterCategory.begin(), filterCategory.end(), filterCategory.begin(), ::tolower);

    // Format table headers
    std::cout << "\n-----------------------------------------------------\n";
    std::cout << std::left
        << std::setw(12) << "Date"
        << std::setw(10) << "Amount"
        << std::setw(15) << "Category"
        << "Notes" << std::endl;
    std::cout << "-----------------------------------------------------\n";

    // Display transactions that match the filter (case-insensitive)
    bool found = false;
    for (const auto& t : transactions) {
        std::string storedCategory = t.getCategory();
        std::transform(storedCategory.begin(), storedCategory.end(), storedCategory.begin(), ::tolower);

        if (filterCategory.empty() || storedCategory == filterCategory) {
            std::cout << std::left
                << std::setw(12) << t.getDate()
                << std::setw(10) << std::fixed << std::setprecision(2) << t.getAmount()
                << std::setw(15) << t.getCategory()
                << t.getNotes() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found for the selected category.\n";
    }
}



/**
 * Generates a summary of transactions within a specified date range.
 * Allows users to filter by date before exporting reports.
 */
void handleGenerateReports(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions to generate reports.\n";
        return;
    }

    // Get date range from the user
    std::string startDate, endDate;
    std::cout << "Enter start date (YYYY-MM-DD) or press Enter to skip: ";
    std::getline(std::cin, startDate);
    std::cout << "Enter end date (YYYY-MM-DD) or press Enter to skip: ";
    std::getline(std::cin, endDate);

    // Filter transactions by date range
    std::vector<Transaction> filteredTransactions;
    for (const auto& transaction : transactions) {
        if ((!startDate.empty() && transaction.getDate() < startDate) ||
            (!endDate.empty() && transaction.getDate() > endDate)) {
            continue;  // Skip transactions outside the selected range
        }
        filteredTransactions.push_back(transaction);
    }

    // Save filtered transactions to a report file
    std::string reportFile = "report.csv";
    saveReportToFile(filteredTransactions, reportFile);
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
    while (true) {
        std::cout << "Are you sure you want to clear all transactions? (y/n): ";
        std::cin >> confirm;
        confirm = std::tolower(confirm);

        if (confirm == 'y' || confirm == 'n') {
            break; // Valid input
        }

        std::cout << "Invalid input. Please enter 'y' for Yes or 'n' for No.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    }

    if (confirm == 'y') {
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
   
    std::cout << "Enter transaction date (YYYY-MM-DD) [default: " << currentDate << "]: ";
    std::getline(std::cin, date);
    if (date.empty()) {
        date = currentDate; // Default to today's date
    }

    // Validate amount input
    while (true) {
        std::cout << "Enter transaction amount: ";
        std::cin >> amount;
        if (std::cin.fail() || amount < 0) {
            std::cout << "Invalid amount. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    std::cin.ignore(); // Clear input buffer after numeric input

    //Ensures Category is not empty
    do {
        std::cout << "Enter transaction category: ";
        std::getline(std::cin, category);
        if (category.empty()) {
            std::cout << "Category cannot be empty. Please enter a valid category.\n";
        }
    } while (category.empty());

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

    // Check if file exists before loading
    std::ifstream fileCheck(filename);
    if (!fileCheck.is_open()) {
        std::cout << "Warning: '" << filename << "' does not exist. A new file will be created upon exit.\n";
    }
    fileCheck.close();

    // Load transactions from file
    loadTransactionsFromFile(transactions, filename);

    int choice;
    do {
        showMainMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Fully clears input buffer


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
            std::cout << "Saving transactions...\n";
            saveTransactionsToFile(transactions, filename);
            std::cout << "Exiting VaultWise. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
