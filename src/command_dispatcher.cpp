#include "command_dispatcher.h"



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
int CommandDispatcher::run_add_block(int amount, std::string send_addr){
    Database curr_db = chain_context->get_database();
    TransactionOutput output_tx(amount, send_addr);
    std::string x = curr_db.get_data(curr_db.get_last_hash_value());
    nlohmann::json json_data = nlohmann::json::parse(x);
    std::string previous_block_tx_id = json_data["block_tx_id"];
    TransactionInput input_tx(previous_block_tx_id, "WalletAddress", 1);
    srand(time(NULL));
    auto v1 = std::rand() % 100;
    std::string random_tx_id = "Transaction number: ";
    random_tx_id += std::to_string(v1);    
    Transaction blah(random_tx_id, input_tx, output_tx);
    chain_context->new_block(blah);
    return 0;
}

/*
    Print out the entire database structure, including internal keys. 
*/
int CommandDispatcher::run_dump_chain(){
    // The first get_database call returns the Database object in the Blockchain context
    // The second one returns the actual leveldb pointer
    leveldb::DB *curr_db = chain_context->get_database().get_database();
    BlockchainIterator printer(curr_db);
    printer.print_all_kv();
    return 0;
}

int CommandDispatcher::run_delete_chain(){
    Database curr_db = chain_context->get_database();
    std::string db = chain_context->get_db_location();
    std::cout << "Database found in: " << db << std::endl;
    std::cout << "Do you want to delete it? y/n: " << std::endl;
    std::string answer;
    std::getline(std::cin, answer);
    if (answer == "y"){
        std::string cmd_line = std::string("rm -rf ") + db.c_str();
        system(cmd_line.c_str()); 
        curr_db.delete_database();
        std::cout<<"Database and block chain deleted!"<<std::endl; 
        exit(0);
    }        
    else{
        std::cout<<"Not deleted."<<std::endl; 
        return 0;
    }
}

int CommandDispatcher::run_pretty_print(){
    leveldb::DB *curr_db = chain_context->get_database().get_database();
    BlockchainIterator printer(curr_db);
    printer.pretty_print();
    return 0;
}

int CommandDispatcher::print_help(){
    std::cout<<"---Supported Commands---"<<std::endl;
    std::cout<<"<add_block> or <a>: Add a new block to the blockchain"<<std::endl;
    std::cout<<"<delete_chain> or <delete>: Deletes the blockchain and the associated data"<<std::endl;
    std::cout<<"<dump_chain> or <dump>: Print out the entire database structure, including internal keys."<<std::endl;
    std::cout<<"<print_chain> or <p>: Nicely display the blockchain contents"<<std::endl;
    std::cout<<"<help>: Show this help menu."<<std::endl;
    return 0;
}

