#ifndef FUND_H
#define FUND_H

#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class Fund {
public:
    Fund();
    Fund(string name);
    Fund(string name, int initialAmount);

    string GetName() const;
    int GetBalance() const;

    bool Deposit(int amount);
    bool Withdraw(int amount);

    void RecordTransaction(const Transaction &transaction);
    void PrintTransactionHistory() const;
    bool HasHistory() const;

private:
    string name_;
    int balance_;
    vector<Transaction> transactionHistory_;
};

#endif  