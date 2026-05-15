# cpp-jolly-banker

A bank transaction processing system that reads commands from a file, manages customer accounts with multiple investment funds, and supports deposits, withdrawals, transfers, and transaction history queries.

## Features

- Accounts stored in a **Binary Search Tree** indexed by account ID
- Each account holds **10 named investment funds**
- Linked fund fallback — if a fund has insufficient balance, it can draw from its linked fund (Money Market ↔ Prime Money Market, Long-Term Bond ↔ Short-Term Bond)
- Full transaction history per fund
- Failed transactions are recorded and marked

## Files

| File | Description |
|---|---|
| `main.cpp` | Entry point |
| `Bank.h / .cpp` | Reads and processes transaction queue |
| `Account.h / .cpp` | Customer account with 10 funds |
| `Fund.h / .cpp` | Individual fund with balance and history |
| `Transaction.h / .cpp` | Transaction parser and executor |
| `BSTree.h / .cpp` | Binary search tree for account storage |
| `bank_trans_out.txt` | Sample output |
| `bank_trans_err.txt` | Sample error output |

## Compile & Run

```bash
g++ -std=c++17 -Wall -o jolly_banker main.cpp Bank.cpp Account.cpp Fund.cpp Transaction.cpp BSTree.cpp
./jolly_banker <transaction_file>
```

## Transaction File Format

```
O 1234 0 Smith John       # Open account ID 1234, deposit $0 into fund 0
D 1234 0 5000             # Deposit $5000 into account 1234, fund 0
W 1234 0 200              # Withdraw $200 from account 1234, fund 0
T 1234 0 5678 1 1000      # Transfer $1000 from 1234/fund0 to 5678/fund1
H 1234                    # Print full transaction history for account 1234
F 1234 0                  # Print transaction history for account 1234, fund 0
```

## Fund Index Reference

| Index | Fund Name |
|---|---|
| 0 | Money Market |
| 1 | Prime Money Market |
| 2 | Long-Term Bond |
| 3 | Short-Term Bond |
| 4 | 500 Index Fund |
| 5 | Capital Value Fund |
| 6 | Growth Equity Fund |
| 7 | Growth Index Fund |
| 8 | Value Fund |
| 9 | Value Stock Index |

## Concepts Covered

- Binary search trees
- Queue-based transaction processing
- Object-oriented design (multiple interacting classes)
- Linked fund overdraft handling
- File I/O and error handling
