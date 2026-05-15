#include "Bank.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        cerr << "ERROR: jolly_banker <input_file>" << endl;
        return 1;
    }

    Bank bank;
    bank.ReadTransactions(argv[1]);
    bank.ProcessTransactions();
    bank.PrintAllAccounts();

    return 0;
}