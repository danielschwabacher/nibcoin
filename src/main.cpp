#include <iostream>
#include <algorithm>
#include <leveldb/db.h>
#include <stdlib.h>

#include "command_dispatcher.h"
#include "../lib/args.hxx"


/*

*/
int main(int argc, char** argv){ 
    const int HASH_DIFF = 3;
    args::ArgumentParser parser("Blockchain CLI.", "");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    // Handles building a new blockchain
    args::Group create_group(parser, "", args::Group::Validators::AllOrNone);
    args::Positional<std::string> create(create_group, "create", "Create a new blockchain, given an initial address and database file. Usage: create <address> <db_location>");
    args::ValueFlag<std::string> addr(create_group, "coinbase_address", "The address which will recieve the mining reward upon validation of the genesis block.", {"coinbase_address", "coinbase", "address"});
    args::ValueFlag<std::string> db_loc(create_group, "database", "The LevelDB file which will store the blockchain data.", {"database", "db"});
    // Handles adding a block to the blockchain
    args::Group add_block_group(parser, "", args::Group::Validators::AllOrNone);
    args::Positional<std::string> add(add_block_group, "add", "Adds a dummy block to the chain containing arbritrary transaction data.");
    args::ValueFlag<std::string> send_address(add_block_group, "txin", "", {"txin", "send_address"});
    args::ValueFlag<std::string> num_coins(add_block_group, "num_coins", "The number of coins to send.", {"num_coins", "coins"});
    args::ValueFlag<std::string> database_add_block(add_block_group, "database", "The LevelDB file to update upon completion.", {"database", "db"});
    // Handles deleting blockchain levelDB files
    args::Group delete_group(parser, "", args::Group::Validators::AllOrNone);
    args::Positional<std::string> delete_chain(delete_group, "delete", "Removes the database file found in <database>");
    args::ValueFlag<std::string> database_delete(delete_group, "database", "The LevelDB file to delete.", {"database", "db"});
    // Handles printing out the chain details
    args::Group print_group(parser, "", args::Group::Validators::AllOrNone);
    args::Positional<std::string> print(print_group, "print", "Nicely displays the blockchain data in <database>");
    args::ValueFlag<std::string> database_print(print_group, "database", "The LevelDB file to print out.", {"database", "db"});
    // Handles dumping out the blockchain file.
    args::Group dump_group(parser, "", args::Group::Validators::AllOrNone);
    args::Positional<std::string> dump(dump_group, "dump", "Dump out the info in the <database> file. No formatting.");
    args::ValueFlag<std::string> database_dump(dump_group, "database", "The LevelDB file to dump out.", {"database", "db"});
    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    // int converted_zeros = atoi(argv[1]);
    std::string database_location = args::get(db_loc);
    Blockchain primary_blockchain(HASH_DIFF, database_location);
    // CommandDispatcher dispatch(&primary_blockchain);
    /*
    while (true){
        std::cout<<"Enter a command, <help> for help menu: ";
        std::getline(std::cin, command);     
        command.erase(std::remove(command.begin(), command.end(), ' '), command.end()); 
        if (command == "stop")
            exit(0);
        else if (command == "exit")
            exit(0);
        else if (command == "quit" || command == "q")
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
    */
    return 0;
}