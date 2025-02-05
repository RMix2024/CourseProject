#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

// ReportGenerator.h
// Defines functions for generating and saving transaction reports.

#include <vector>
#include <string>
#include "Transaction.h"

// Saves transaction details into a CSV report file.
void saveReportToFile(const std::vector<Transaction>& transactions, const std::string& reportFilename);

// Generates a category-based spending summary from transactions.
void generateCategorySummary(const std::vector<Transaction>& transactions);

#endif // REPORTGENERATOR_H
