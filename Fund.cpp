#include "Fund.h"
#include <iostream>

using namespace std;

Fund::Fund() {
    name_ = "";
    balance_ = 0;
}

Fund::Fund(string name) {
    name_ = name;
    balance_ = 0;
}

Fund::Fund(string name, int initialAmount) {
    name_ = name;
    balance_ = initialAmount;
}

string Fund::GetName() const {
    return name_;
}

int Fund::GetBalance() const {
    return balance_;
}

bool Fund::Deposit(int amount) {
    if (amount < 0) {
        return false;
    }
    balance_ += amount;
    return true;
}

bool Fund::Withdraw(int amount) {
    if (amount < 0) {
        return false;
    }
    if (amount > balance_) {
        return false;
    }
    balance_ -= amount;
    return true;
}

void Fund::RecordTransaction(const Transaction &transaction) {
    transactionHistory_.push_back(transaction);
}

void Fund::PrintTransactionHistory() const {
    for (const Transaction &t : transactionHistory_) {
        cout << "  " << t.ToString() << endl;
    }
}

bool Fund::HasHistory() const {
    return !transactionHistory_.empty();
}