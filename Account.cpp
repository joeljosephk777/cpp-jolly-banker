#include "Account.h"
#include <iostream>

using namespace std;

const string FUND_NAMES[10] = {
    "Money Market",
    "Prime Money Market",
    "Long-Term Bond",
    "Short-Term Bond",
    "S+P Index Fund",
    "Value Fund",
    "Growth Equity Fund",
    "Growth Index Fund",
    "Crypto ETF",
    "Precious Metals ETF"
};

Account::Account() {
    first_name_ = "";
    last_name_ = "";
    seed_fund_ = 0;
    id_ = 0;
    for (int i = 0; i < 10; i++) {
        funds_[i] = Fund(FUND_NAMES[i]);
    }
}

Account::Account(string firstName, string lastName, int id, int seedFund) {
    first_name_ = firstName;
    last_name_ = lastName;
    id_ = id;
    seed_fund_ = seedFund;
    for (int i = 0; i < 10; i++) {
        if (i == seedFund) {
            funds_[i] = Fund(FUND_NAMES[i], 250);
        } else {
            funds_[i] = Fund(FUND_NAMES[i]);
        }
    }
}

int Account::GetId() const {
    return id_;
}

string Account::GetFirstName() const {
    return first_name_;
}

string Account::GetLastName() const {
    return last_name_;
}

int Account::GetFundBalance(int fundId) const {
    if (fundId < 0 || fundId > 9) {
        return -1;
    }
    return funds_[fundId].GetBalance();
}

bool Account::IsLinkableFund(int fundId) const {
    return (fundId == 0 || fundId == 1 || fundId == 2 || fundId == 3);
}

int Account::GetLinkedFund(int fundId) const {
    if (fundId == 0) return 1;
    if (fundId == 1) return 0;
    if (fundId == 2) return 3;
    if (fundId == 3) return 2;
    return -1;
}

bool Account::CoverWithLinkedFund(int fundId, int amount) {
    if (!IsLinkableFund(fundId)) {
        return false;
    }

    int linkedFund = GetLinkedFund(fundId);
    int totalAvailable = funds_[fundId].GetBalance() + funds_[linkedFund].GetBalance();

    if (totalAvailable < amount) {
        return false;
    }

    int fromPrimary = funds_[fundId].GetBalance();
    int fromLinked = amount - fromPrimary;

    funds_[fundId].Withdraw(fromPrimary);
    funds_[linkedFund].Withdraw(fromLinked);

    return true;
}

// Deposit into a fund
bool Account::Deposit(int fundId, int amount, const Transaction &transaction) {
    if (fundId < 0 || fundId > 9) {
        cerr << "ERROR: Invalid fund ID: " << fundId << endl;
        return false;
    }

    bool success = funds_[fundId].Deposit(amount);
    funds_[fundId].RecordTransaction(transaction);
    return success;
}

// Withdraw from a fund
bool Account::Withdraw(int fundId, int amount, const Transaction &transaction) {
    if (fundId < 0 || fundId > 9) {
        cerr << "ERROR: Invalid fund ID: " << fundId << endl;
        return false;
    }

    // Try normal withdrawal
    if (funds_[fundId].Withdraw(amount)) {
        funds_[fundId].RecordTransaction(transaction);
        return true;
    }

    // Try linked fund coverage
    if (IsLinkableFund(fundId) && CoverWithLinkedFund(fundId, amount)) {
        funds_[fundId].RecordTransaction(transaction);
        int linkedFund = GetLinkedFund(fundId);
        funds_[linkedFund].RecordTransaction(transaction);
        return true;
    }

    // Failed
    Transaction failedT = transaction;
    failedT.SetFailed();
    funds_[fundId].RecordTransaction(failedT);
    cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << first_name_ << " " << last_name_ << " " << FUND_NAMES[fundId] << endl;
    return false;
}

// Transfer between funds
bool Account::Transfer(int fromFund, Account &toAccount, int toFund, int amount, const Transaction &transaction) {
    if (fromFund < 0 || fromFund > 9 || toFund < 0 || toFund > 9) {
        cerr << "ERROR: Invalid fund ID" << endl;
        return false;
    }

    // Check if transferring between linked funds in same account
    bool sameAccount = (id_ == toAccount.GetId());
    bool linkedTransfer = sameAccount && IsLinkableFund(fromFund) && (GetLinkedFund(fromFund) == toFund);

    //  eroor if linked fund transfer
    if (linkedTransfer) {
        if (funds_[fromFund].GetBalance() < amount) {
            Transaction failedT = transaction;
            failedT.SetFailed();
            funds_[fromFund].RecordTransaction(failedT);
            cerr << "ERROR: Not enough funds to transfer " << amount << " from " << first_name_ << " " << last_name_ << " " << FUND_NAMES[fromFund] << endl;
            return false;
        }
    }


    if (funds_[fromFund].Withdraw(amount)) {
        toAccount.funds_[toFund].Deposit(amount);
        funds_[fromFund].RecordTransaction(transaction);
        toAccount.funds_[toFund].RecordTransaction(transaction);
        return true;
    }

    if (!linkedTransfer && IsLinkableFund(fromFund) && CoverWithLinkedFund(fromFund, amount)) {
        toAccount.funds_[toFund].Deposit(amount);
        funds_[fromFund].RecordTransaction(transaction);
        int linkedFund = GetLinkedFund(fromFund);
        funds_[linkedFund].RecordTransaction(transaction);
        toAccount.funds_[toFund].RecordTransaction(transaction);
        return true;
    }

    // Failed
    Transaction failedT = transaction;
    failedT.SetFailed();
    funds_[fromFund].RecordTransaction(failedT);
    cerr << "ERROR: Not enough funds to transfer " << amount << " from " << first_name_ << " " << last_name_ << " " << FUND_NAMES[fromFund] << endl;
    return false;
}

// Print history for account (all funds)
void Account::PrintHistory() const {
    cout << "Transaction History for " << first_name_ << " " << last_name_ << " (by fund)" << endl;
    cout << "Opening trans: O " << id_ << " " << seed_fund_ << " " << last_name_ << " " << first_name_ << endl;
    for (int i = 0; i < 10; i++) {
        if (funds_[i].HasHistory()) {
            cout << FUND_NAMES[i] << ": $" << funds_[i].GetBalance() << endl;
            funds_[i].PrintTransactionHistory();
        }
    }
}

// Print history for one fund
void Account::PrintFundHistory(int fundId) const {
    if (fundId < 0 || fundId > 9) {
        cerr << "ERROR: Invalid fund ID: " << fundId << endl;
        return;
    }
    cout << "Transaction History for " << first_name_ << " " << last_name_ << " " << FUND_NAMES[fundId] << ": $" << funds_[fundId].GetBalance() << endl;
    funds_[fundId].PrintTransactionHistory();
}

ostream& operator<<(ostream &out, const Account &acct) {
    out << acct.first_name_ << " " << acct.last_name_ << " Account ID: " << acct.id_ << endl;
    for (int i = 0; i < 10; i++) {
        out << "    " << FUND_NAMES[i] << ": $" << acct.funds_[i].GetBalance() << endl;
    }
    return out;
}