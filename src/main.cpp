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
        if (command == "stop")
            exit(0);
        else if (command == "exit")
            exit(0);
        else if (command == "quit")
            exit(0);
        else if (command == "add_block")
            dispatch.run_add_block();
        else if (command == "dump_chain")
            dispatch.run_dump_chain();
        else if (command == "print_chain")
            dispatch.run_pretty_print();
        else if (command == "delete_chain")
            dispatch.run_delete_chain();
        else if (command == "help")
            dispatch.print_help();
        else{
            std::cout<<"Invalid input, try again"<<std::endl;
        }
    }
    return 0;
}
