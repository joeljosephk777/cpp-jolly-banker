#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include "Fund.h"
#include "Transaction.h"

using namespace std;

class Account {
public:
    
    Account();
    Account(string firstName, string lastName, int id, int seedFund);

    int GetId() const;
    string GetFirstName() const;
    string GetLastName() const;
    int GetFundBalance(int fundId) const;

    bool Deposit(int fundId, int amount, const Transaction &transaction);
    bool Withdraw(int fundId, int amount, const Transaction &transaction);
    bool Transfer(int fromFund, Account &toAccount, int toFund, int amount, const Transaction &transaction);

    void PrintHistory() const;
    void PrintFundHistory(int fundId) const;

    friend ostream& operator<<(ostream &out, const Account &acct);

private:
    string first_name_;
    string last_name_;
    int id_;
    int seed_fund_;
    Fund funds_[10];

    bool CoverWithLinkedFund(int fundId, int amount);
    int GetLinkedFund(int fundId) const;
    bool IsLinkableFund(int fundId) const;
};

#endif