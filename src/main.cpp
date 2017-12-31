#include <iostream>
#include <leveldb/db.h>
#include "block.h"
#include "blockchain.h"
#include "Serialization.h"
#include "chain_iterator.h"
#include "command_dispatcher.h"
#include "../lib/json.hpp"

/*

*/
int main(){ 
    Blockchain primary_blockchain;
    // primary_blockchain.new_block("First block");
    // primary_blockchain.new_block("Second block");
    // leveldb::DB *primary_database = primary_blockchain.get_database();
    // BlockchainIterator printer(primary_database);
    // printer.print_all_kv();
    CommandDispatcher dispatch(&primary_blockchain);
    std::string command;
    while (true){
        std::cout<<"Enter a command: ";
        std::cin >> command;
        std::cout<<"Entered: " << command << std::endl;
        if (command == "stop")
            exit(0);
        else if (command == "exit")
            exit(0);
        else if (command == "quit")
            exit(0);
        else if (command == "add_block")
            dispatch.run_add_block();
        else if (command == "print_chain")
            dispatch.run_print_chain();
        else{
            std::cout<<"Invalid input, try again"<<std::endl;
        }
    }
    return 0;
}
