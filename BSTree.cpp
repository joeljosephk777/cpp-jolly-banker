#include "BSTree.h"
#include <iostream>

using namespace std;

BSTree::BSTree() {
    root_ = nullptr;
}

BSTree::BSTree(const BSTree &tree) {
    root_ = CopyTree(tree.root_);
}

BSTree::~BSTree() {
    DestroyTree(root_);
}

void BSTree::DestroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node->p_acct;
    delete node;
}

BSTree::Node* BSTree::CopyTree(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    Node* newNode = new Node();
    newNode->p_acct = new Account(*(node->p_acct));
    newNode->left = CopyTree(node->left);
    newNode->right = CopyTree(node->right);
    return newNode;
}

bool BSTree::Insert(Account* account) {
    if (account == nullptr) {
        return false;
    }

    Node* newNode = new Node();
    newNode->p_acct = account;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (root_ == nullptr) {
        root_ = newNode;
        return true;
    }

    Node* current = root_;
    while (true) {
        if (account->GetId() == current->p_acct->GetId()) {
            delete newNode;
            return false;
        }

        else if (account->GetId() < current->p_acct->GetId()) {
            if (current->left == nullptr) {
                current->left = newNode;
                return true;
            }
            current = current->left;
        }

        else {
            if (current->right == nullptr) {
                current->right = newNode;
                return true;
            }
            current = current->right;
        }
    }
}

bool BSTree::Retrieve(const int &account_id, Account* &account) const {
    Node* current = root_;

    while (current != nullptr) {
        if (account_id == current->p_acct->GetId()) {
            account = current->p_acct;
            return true;
        }
        else if (account_id < current->p_acct->GetId()) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    account = nullptr;
    return false;
}

bool BSTree::Delete(const int &account_id, Account* &account) {
    Node* current = root_;
    Node* parent = nullptr;

    // Find the node to delete
    while (current != nullptr && current->p_acct->GetId() != account_id) {
        parent = current;
        if (account_id < current->p_acct->GetId()) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Not found
    if (current == nullptr) {
        account = nullptr;
        return false;
    }

    account = current->p_acct;

    // Case 1: Node has no children (leaf)
    if (current->left == nullptr && current->right == nullptr) {
        if (current == root_) {
            root_ = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    }
    // Case 2: Node has one child
    else if (current->left == nullptr || current->right == nullptr) {
        Node* child = (current->left != nullptr) ? current->left : current->right;

        if (current == root_) {
            root_ = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    }
    // Case 3: Node has two children
    else {
        // Find in-order successor (smallest in right subtree)
        Node* successorParent = current;
        Node* successor = current->right;

        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        current->p_acct = successor->p_acct;

        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        delete successor;
    }

    return true;
}

void BSTree::DisplayHelper(Node* node) const {
    if (node == nullptr) {
        return;
    }
    DisplayHelper(node->left);
    cout << *(node->p_acct) << endl;
    DisplayHelper(node->right);
}

void BSTree::Display() const {
    DisplayHelper(root_);
}

int BSTree::SizeHelper(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + SizeHelper(node->left) + SizeHelper(node->right);
}

int BSTree::Size() const {
    return SizeHelper(root_);
}

BSTree& BSTree::operator=(const BSTree &tree) {
    if (this != &tree) {
        DestroyTree(root_);
        root_ = CopyTree(tree.root_);
    }
    return *this;
}