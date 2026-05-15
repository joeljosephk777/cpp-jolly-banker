#include "Bank.h"
#include <fstream>
#include <iostream>

using namespace std;

Bank::Bank() {
}

void Bank::ReadTransactions(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERROR: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            Transaction t(line);
            transactions_.push(t);
        }
    }
    file.close();
}

void Bank::ProcessTransactions() {
    while (!transactions_.empty()) {
        Transaction t = transactions_.front();
        transactions_.pop();

        char type = t.GetType();

        if (type == 'O') {
            ExecuteOpen(t);
        }
        else if (type == 'D') {
            ExecuteDeposit(t);
        }
        else if (type == 'W') {
            ExecuteWithdraw(t);
        }
        else if (type == 'T') {
            ExecuteTransfer(t);
        }
        else if (type == 'H') {
            ExecuteHistory(t);
        }
        else if (type == 'F') {
            ExecuteFundHistory(t);
        }
    }
}

void Bank::PrintAllAccounts() {
    cout << "\nFinal Balances:" << endl;
    accounts_.Display();
}


void Bank::ExecuteOpen(const Transaction &t) {
    Account* existing = nullptr;
    if (accounts_.Retrieve(t.GetAccountID(), existing)) {
        cerr << "ERROR: Account " << t.GetAccountID() << " already exists" << endl;
        return;
    }

    Account* newAccount = new Account(t.GetFirstName(), t.GetLastName(), t.GetAccountID(), t.GetFundID());
    accounts_.Insert(newAccount);
}

void Bank::ExecuteDeposit(const Transaction &t) {
    Account* account = nullptr;
    if (!accounts_.Retrieve(t.GetAccountID(), account)) {
        cerr << "ERROR: Account " << t.GetAccountID() << " not found" << endl;
        return;
    }

    account->Deposit(t.GetFundID(), t.GetAmount(), t);
}

void Bank::ExecuteWithdraw(const Transaction &t) {
    Account* account = nullptr;
    if (!accounts_.Retrieve(t.GetAccountID(), account)) {
        cerr << "ERROR: Account " << t.GetAccountID() << " not found" << endl;
        return;
    }

    account->Withdraw(t.GetFundID(), t.GetAmount(), t);
}

void Bank::ExecuteTransfer(const Transaction &t) {
    Account* fromAccount = nullptr;
    Account* toAccount = nullptr;

    if (!accounts_.Retrieve(t.GetAccountID(), fromAccount)) {
        cerr << "ERROR: Account " << t.GetAccountID() << " not found" << endl;
        return;
    }

    if (!accounts_.Retrieve(t.GetTargetAccountID(), toAccount)) {
        cerr << "ERROR: Account " << t.GetTargetAccountID() << " not found" << endl;
        return;
    }

    fromAccount->Transfer(t.GetFundID(), *toAccount, t.GetTargetFundID(), t.GetAmount(), t);
}

void Bank::ExecuteHistory(const Transaction &t) {
    Account* account = nullptr;
    if (!accounts_.Retrieve(t.GetAccountID(), account)) {
        cerr << "ERROR: Account " << t.GetAccountID() << " not found" << endl;
        return;
    }

    account->PrintHistory();
}

void Bank::ExecuteFundHistory(const Transaction &t) {
    Account* account = nullptr;
    if (!accounts_.Retrieve(t.GetAccountID(), account)) {
        cerr << "ERROR: Account " << t.GetAccountID() << " not found" << endl;
        return;
    }

    account->PrintFundHistory(t.GetFundID());
}
