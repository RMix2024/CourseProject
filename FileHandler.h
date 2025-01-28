#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include "Transaction.h"

void saveTransactionsToFile(const std::vector<Transaction>& transactions, const std::string& filename);
void loadTransactionsFromFile(std::vector<Transaction>& transactions, const std::string& filename);
void deleteTransactionFile(const std::string& filename);



#endif // FILEHANDLER_H
