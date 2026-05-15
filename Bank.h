#ifndef BANK_H
#define BANK_H

#include <string>
#include <queue>
#include "Transaction.h"
#include "BSTree.h"

using namespace std;

class Bank {
public:
    Bank();

    void ReadTransactions(string filename);
    void ProcessTransactions();
    void PrintAllAccounts();

private:
    BSTree accounts_;
    queue<Transaction> transactions_;

    void ExecuteOpen(const Transaction &t);
    void ExecuteDeposit(const Transaction &t);
    void ExecuteWithdraw(const Transaction &t);
    void ExecuteTransfer(const Transaction &t);
    void ExecuteHistory(const Transaction &t);
    void ExecuteFundHistory(const Transaction &t);
};

#endif