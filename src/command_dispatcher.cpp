#include "blockchain.h"
#include "block.h"
#include "Serialization.h"
#include "command_dispatcher.h"
#include "chain_iterator.h"
#include "database.h"
#include <string>
#include <cassert>
#include <leveldb/db.h>

/*
    A CommandDispatcher handles running operations entered 
    into the command line. 

    Each CommandDispatcher holds a single command to run, thus
    for each command issued, a new CommandDispatcher needs to be
    created. 

    The CommandDispatcher can deal with the following commands:
        - add_block <block_data> ------> Adds a block to the primary blockchain.
        - print_chain -----> Prints all the key value pairs found in the database file.
*/
CommandDispatcher::CommandDispatcher(Blockchain *context){
    chain_context = context; 
}

/*
    Run the command the CommandDispatcher holds in context. 
*/
int CommandDispatcher::run_add_block(){
    Database curr_db = chain_context->get_database();
    std::string block_data;
    std::cout<<"Enter block data to store: ";
    std::cin.ignore();
    std::getline(std::cin, block_data); 
    chain_context->new_block(block_data);
    return 0;
}

int CommandDispatcher::run_print_chain(){
    // The first get_database call returns the Database object in the Blockchain context
    // The second one returns the actual leveldb pointer
    leveldb::DB *curr_db = chain_context->get_database().get_database();
    BlockchainIterator printer(curr_db);
    printer.print_all_kv();
    return 0;
}

int CommandDispatcher::run_delete_chain(){
    Database curr_db = chain_context->get_database();    
    system("rm -rf /tmp/blocks");
    std::cout<<"Database and block chain deleted!"<<std::endl;
    exit(0);
}