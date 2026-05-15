#include "Transaction.h"
#include <sstream>

using namespace std;


Transaction::Transaction() {
    type_ = ' ';
    account_id_ = 0;
    fund_id_ = 0;
    amount_ = 0;
    target_account_id_ = 0;
    target_fund_id_ = 0;
    first_name_ = "";
    last_name_ = "";
    failed_ = false;
}

Transaction::Transaction(string line) {
    failed_ = false;
    account_id_ = 0;
    fund_id_ = 0;
    amount_ = 0;
    target_account_id_ = 0;
    target_fund_id_ = 0;
    first_name_ = "";
    last_name_ = "";

    stringstream ss(line);
    ss >> type_;

    if (type_ == 'O') {
        ss >> account_id_ >> fund_id_ >> last_name_ >> first_name_;
    }
    else if (type_ == 'D') {
        ss >> account_id_ >> fund_id_ >> amount_;
    }
    else if (type_ == 'W') {
        ss >> account_id_ >> fund_id_ >> amount_;
    }
    else if (type_ == 'T') {
        ss >> account_id_ >> fund_id_ >> target_account_id_ >> target_fund_id_ >> amount_;
    }
    else if (type_ == 'H') {
        ss >> account_id_;
    }
    else if (type_ == 'F') {
        ss >> account_id_ >> fund_id_;
    }
}


char Transaction::GetType() const {
    return type_;
}

int Transaction::GetAccountID() const {
    return account_id_;
}

int Transaction::GetFundID() const {
    return fund_id_;
}

int Transaction::GetAmount() const {
    return amount_;
}

int Transaction::GetTargetAccountID() const {
    return target_account_id_;
}

int Transaction::GetTargetFundID() const {
    return target_fund_id_;
}

string Transaction::GetFirstName() const {
    return first_name_;
}

string Transaction::GetLastName() const {
    return last_name_;
}

bool Transaction::IsFailed() const {
    return failed_;
}

void Transaction::SetFailed() {
    failed_ = true;
}

// Used to print out history
string Transaction::ToString() const {
    stringstream ss;

    if (type_ == 'O') {
        ss << "O " << account_id_ << " " << fund_id_ << " " << last_name_ << " " << first_name_;
    }
    else if (type_ == 'D') {
        ss << "D " << account_id_ << " " << fund_id_ << " " << amount_;
    }
    else if (type_ == 'W') {
        ss << "W " << account_id_ << " " << fund_id_ << " " << amount_;
    }
    else if (type_ == 'T') {
        ss << "T " << account_id_ << " " << fund_id_ << " " << target_account_id_ << " " << target_fund_id_ << " " << amount_;
    }
    else if (type_ == 'H') {
        ss << "H " << account_id_;
    }
    else if (type_ == 'F') {
        ss << "F " << account_id_ << " " << fund_id_;
    }

    if (failed_) {
        ss << " (Failed)";
    }

    return ss.str();
}