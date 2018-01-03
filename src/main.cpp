#include <iostream>
#include <algorithm>
#include <leveldb/db.h>
#include <stdlib.h>

#include "block.h"
#include "blockchain.h"
#include "Serialization.h"
#include "chain_iterator.h"
#include "command_dispatcher.h"
#include "../lib/json.hpp"

/*

*/
int main(int argc, char** argv){ 
    if (argc != 3){
        std::cout<<"Usage: ./blockchain.out <number of leading zeros in hash> <database location>"<<std::endl;
        exit(0);
    }
    int converted_zeros = atoi(argv[1]);
    std::string database_location = argv[2];

    Blockchain primary_blockchain(converted_zeros, database_location);
    CommandDispatcher dispatch(&primary_blockchain);

    std::string command;
    while (true){
        std::cout<<"Enter a command: ";
        std::getline(std::cin, command);     
        command.erase(std::remove(command.begin(), command.end(), ' '), command.end()); 
        if (command == "stop")
            exit(0);
        else if (command == "exit")
            exit(0);
        else if (command == "quit")
            exit(0);
        else if (command == "add_block" || command == "a")
            dispatch.run_add_block();
        else if (command == "dump_chain" || command == "dump")
            dispatch.run_dump_chain();
        else if (command == "print_chain" || command == "p")
            dispatch.run_pretty_print();
        else if (command == "delete_chain" || command == "delete")
            dispatch.run_delete_chain(); 
        else if (command == "help")
            dispatch.print_help();
        else{
            std::cout<<"Invalid input, try again"<<std::endl;
        }
    }
    return 0;
}