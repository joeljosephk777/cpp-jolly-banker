#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

class Transaction {
public:
    Transaction();
    Transaction(string line);

    char GetType() const;
    int GetAccountID() const;
    int GetFundID() const;
    int GetAmount() const;
    int GetTargetAccountID() const;
    int GetTargetFundID() const;
    string GetFirstName() const;
    string GetLastName() const;
    bool IsFailed() const;

    void SetFailed();
    string ToString() const;

private:
    char type_;
    int account_id_;
    int fund_id_;
    int amount_;
    int target_account_id_;
    int target_fund_id_;
    string first_name_;
    string last_name_;
    bool failed_;
};

#endif  