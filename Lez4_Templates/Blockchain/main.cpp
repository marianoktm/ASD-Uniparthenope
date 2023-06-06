//
// Created by apont on 1/2/2023.
//


#include <iostream>
#include <ctime>
#include "node.h"
#include "linkedlist.h"
#include "blockchain.h"


void populate_blockchain(blockchain * bc) {
    std::string users = "ABCDEFGHI";
    int iterations = 40;
    int max_transaction = 3000;

    std::srand(std::time(nullptr)+1);

    int rand1, rand2;
    rand1 = rand2 = 0;
    for (int i = 0; i < iterations; i++) {
        rand1 = std::rand() % users.size();
        rand2 = std::rand() % users.size();

        while (rand1 == rand2) rand2 = std::rand() % users.size();

        std::string from;
        std::string to;
        from += users.at(rand1);
        to += users.at(rand2);

        auto transaction_to_add = new transaction(i, from, to, std::rand()%max_transaction);

        if (std::rand() % 100 < 35)
            bc->new_block(*transaction_to_add);
        else
            bc->push_transaction(*transaction_to_add, std::rand()%bc->get_size());
    }
}

int main() {
    // Test node constructor
    node<int> node1(10, nullptr);
    node<int> node2(13, nullptr);
    node<int> node3(15, nullptr);


    // Test set_next
    node1.set_next(&node2);
    node2.set_next(&node3);


    // Test print
    auto temp = &node1;
    do {
        std::cout << temp->get_data() << " ";
    } while ((temp = temp->get_next()) != nullptr);
    std::cout << std::endl;


    // Test linked list constructor
    linkedlist<int> list(&node1);
    std::cout << "Size of list: " << list.get_size() << std::endl;


    // Test get i
    std::cout << list.get(0)->get_data() << std::endl;


    // Test get i data
    std::cout << list.get_data(2) << std::endl;

    std::cout << "\n\n\n";


    // !!! BLOCKCHAIN TEST !!!
    std::cout << "====================" << std::endl << "BLOCKCHAIN TESTING" << std::endl << "====================" << std::endl;
    blockchain blockchain;

    // Size
    std::cout << "Blockchain size (newly created): " << blockchain.get_size() << std::endl;

    transaction trans1(1, "A", "B", 150);
    blockchain.new_block(trans1);

    std::cout << "Blockchain size (after new_block() call): " << blockchain.get_size() << std::endl;

    // Populating a blockchain
    populate_blockchain(&blockchain);

    std::cout << "Blockchain size (after populating): " << blockchain.get_size() << std::endl;

    // User balance
    std::cout << "Balance of user A: " << blockchain.get_user_balance("A") << std::endl;

    // Whole blockchain print
    blockchain.print();
    return 0;
}
