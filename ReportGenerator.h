#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <vector>
#include <string>
#include "Transaction.h"

void saveReportToFile(const std::vector<Transaction>& transactions, const std::string& reportFilename);
void generateCategorySummary(const std::vector<Transaction>& transactions);

#endif // REPORTGENERATOR_H
