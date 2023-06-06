//
// Created by apont on 1/3/2023.
//

#ifndef ASD_BLOCKCHAIN_H
#define ASD_BLOCKCHAIN_H

#include <string>
#include <sstream>
#include <iostream>
#include "linkedlist.h"

/**
 * A single blockchain transaction
 */
class transaction {
private:
    unsigned int transaction_no;
    std::string from;
    std::string to;
    double amount;

public:
    transaction() = default;
    transaction(unsigned int transactionNo, const std::string &from, const std::string &to, double amount): transaction_no(transactionNo), from(from), to(to), amount(amount) {}

    unsigned int getTransactionNo() { return transaction_no; }
    void setTransactionNo(unsigned int transactionNo) { transaction_no = transactionNo; }

    const std::string getFrom() { return from; }
    void setFrom(const std::string _from) { transaction::from = _from; }

    const std::string getTo() { return to; }
    void setTo(const std::string _to) { transaction::to = _to; }

    double getAmount() { return amount; }
    void setAmount(double _amount) { transaction::amount = _amount; }

    std::string to_str() {
        std::stringstream stringstream;
        stringstream <<
        "ID: " << transaction_no << std::endl <<
        "From: " << transaction::from << std::endl <<
        "To: " << transaction::to << std::endl <<
        "Amount: " << transaction::amount << std::endl;
        return stringstream.str();
    }

};

/**
 * A block of a blockchain. It's basically a list of transactions
 */
class block: public linkedlist<transaction>{
public:
    block() {}
    block(node<transaction> * head) : linkedlist(head) {}

};

/**
 * The actual Blockchain. It's basically a list of blocks (a list of lists of transactions)
 */
class blockchain: public linkedlist<block> {
public:
    blockchain() {}
    blockchain(node<block> * head) : linkedlist(head) {}

    // Returns "user"'s transaction in a list
    linkedlist<transaction> * get_transactions(std::string user);

    // Creates a new block from a transaction and pushes it back.
    block * new_block(transaction transaction);

    // Push transaction on the i-th block. If i > size, returns false.
    bool push_transaction(transaction t ,unsigned int i);

    // Returns the balance of user.
    double get_user_balance(std::string user);

    // Prints the whole blockchain
    void print();
};


/* BLOCKCHAIN'S METHODS */
// Returns "user"'s transaction in a list
linkedlist<transaction> * blockchain::get_transactions(std::string user) {
    auto out = new linkedlist<transaction>();

    auto temp_blockchain_node = get_head();
    while (temp_blockchain_node->get_next()) { // Iteration through blockchain
        auto temp_block_list = temp_blockchain_node->get_data(); // Getting i-th block list (transaction list)

        auto temp_block_node = temp_block_list.get_head(); // Getting block node
        while (temp_block_node->get_next()) { // Iteration through transaction in block list
            auto transaction = temp_block_node->get_data(); // Getting i-th transaction
            if ((transaction.getFrom() == user) or (transaction.getTo() == user)) { // Checking if user is part of the transaction
                out->push_back(transaction); // Pushing back the transaction
            }
            temp_block_node = temp_block_node->get_next();
        }
        temp_blockchain_node = temp_blockchain_node->get_next();
    }

    return out;
}

// Inserts a new block into the chain
block * blockchain::new_block(transaction _transaction) {
    // Creates a new transaction node
    auto transaction_node = new node<transaction>(_transaction);

    // Creates a new block with transaction_node
    auto new_block = new block(transaction_node);

    // Pushing the new block
    blockchain::push_back(*new_block);

    // Returning the new block pointer
    return new_block;
}

// Pushes a transaction into the i-th block.
bool blockchain::push_transaction(transaction t, unsigned int i) {
    if (i >= blockchain::get_size()) return false;

    // Get i-th block
    auto temp_blockchain_node = blockchain::get_head();
    int k = 0;
    while (temp_blockchain_node->get_next() and k < i) {
        temp_blockchain_node = temp_blockchain_node->get_next();
        k++;
    }

    auto block = temp_blockchain_node->get_data();
    block.push_back(t);

    return true;
}

// Returns the user's balance
double blockchain::get_user_balance(std::string user) {
    auto user_transactions = blockchain::get_transactions(user);

    double balance = 0;

    auto temp_transaction_node = user_transactions->get_head();
    while (temp_transaction_node->get_next() != nullptr) {
        auto transaction = temp_transaction_node->get_data();

        if (transaction.getFrom() == user)
            balance -= transaction.getAmount();
        else if (transaction.getTo() == user)
            balance += transaction.getAmount();

        temp_transaction_node = temp_transaction_node->get_next();
    }

    return balance;
}

// Prints the whole blockchain
void blockchain::print() {
    auto temp_blockchain_node = blockchain::get_head();

    if (temp_blockchain_node == nullptr) {
        std::cout << "the chain is empty..." << std::endl;
        return;
    }

    int i = 0;
    while (temp_blockchain_node->get_next() != nullptr) {
        auto temp_block = temp_blockchain_node->get_data();
        auto temp_block_node = temp_block.get_head();

        std::cout << "======== " << "BLOCK N. " << i << " ========" << std::endl;
        while (temp_block_node->get_next() != nullptr) {
            std::cout << "----------" << std::endl;
            std::cout << temp_block_node->get_data().to_str() << std::endl;
            std::cout << "----------" << std::endl;

            temp_block_node = temp_block_node->get_next();
        }

        temp_blockchain_node = temp_blockchain_node->get_next();
        i++;
    }
}



#endif //ASD_BLOCKCHAIN_H
