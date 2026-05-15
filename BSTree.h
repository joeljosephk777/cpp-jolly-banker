#ifndef BSTREE_H
#define BSTREE_H

#include "Account.h"

class BSTree {
public:
    BSTree();
    BSTree(const BSTree &tree);
    ~BSTree();

    bool Insert(Account *account);
    bool Retrieve(const int &account_id, Account* &account) const;
    bool Delete(const int &account_id, Account* &account);

    void Display() const;
    int Size() const;

    BSTree& operator=(const BSTree &tree);

private:
    struct Node {
        Account* p_acct;
        Node* left;
        Node* right;
    };

    Node* root_;

    void DisplayHelper(Node* node) const;
    int SizeHelper(Node* node) const;
    void DestroyTree(Node* node);
    Node* CopyTree(Node* node);
};

#endif