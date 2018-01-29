#include <iostream>
#include <algorithm>
#include <leveldb/db.h>
#include <stdlib.h>

#include "command_dispatcher.h"
#include "../lib/args.hxx"







void CreateCommand(args::Subparser &parser)
{

    args::Group create_group_arguments(parser, "", args::Group::Validators::AllOrNone);
    args::GlobalOptions globals(parser, create_group_arguments);
    args::ValueFlag<std::string> coinbase_address(create_group_arguments, "coinbase_address", "The address which will recieve the mining reward upon validation of the genesis block.", {"coinbase_address", "coinbase", "address"});
    args::ValueFlag<std::string> db_loc(create_group_arguments, "database", "The LevelDB file which will store the blockchain data.", {"database", "db"});
    // args::ValueFlag<std::string> message(parser, "MESSAGE", "commit message", {'m'});
    parser.Parse();
}


/*
    This is mostly just bootstrapping the command line interface. 
*/
int main(int argc, char** argv){ 
    const int HASH_DIFF = 3;
    args::ArgumentParser parser("Blockchain CLI.", "");
    args::Group commands(parser, "Commands");

    args::Command create(commands, "create", "Create a new blockchain, given an initial address and database file. Usage: create --address=<Reward Address> --database=<Database file location>", &CreateCommand);        
    
    // args::Command add(commands, "add", "Adds a dummy block to the chain containing arbritrary transaction data. Usage: add --txin=<Transaction input> --coins=<Number of coins to send> --database=<Database file location>");
    
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    // Handles building a new blockchain
    // args::Group create_group_arguments(parser, "arguments", args::Group::Validators::AllOrNone);
    // args::ValueFlag<std::string> coinbase_address(create_group_arguments, "coinbase_address", "The address which will recieve the mining reward upon validation of the genesis block.", {"coinbase_address", "coinbase", "address"});
    // args::ValueFlag<std::string> db_loc(create_group_arguments, "database", "The LevelDB file which will store the blockchain data.", {"database", "db"});

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
    
    if (create){
        std::cout<<"Create chain selected."<<std::endl; 
    }
    
    
    /*
        // args::Positional<std::string> create(create_group, "create", "Create a new blockchain, given an initial address and database file. Usage: create --address=<Reward Address> --database=<Database file location>");

    args::ArgumentParser p("git-like parser");
    args::Group commands(p, "commands");
    args::Command add(commands, "add", "add file contents to the index");
    args::Command commit(commands, "commit", "record changes to the repository");
    args::Group arguments(p, "arguments", args::Group::Validators::DontCare, args::Options::Global);
    args::ValueFlag<std::string> gitdir(arguments, "path", "", {"git-dir"});
    args::HelpFlag h(arguments, "help", "help", {'h', "help"});
    args::PositionalList<std::string> pathsList(arguments, "paths", "files to commit");










    // Handles adding a block to the blockchain
    args::Group add_block_group(parser, "", args::Group::Validators::AllOrNone);
    args::Positional<std::string> add(add_block_group, "add", "Adds a dummy block to the chain containing arbritrary transaction data. Usage: add --txin=<Transaction input> --coins=<Number of coins to send> --database=<Database file location>");
    args::ValueFlag<std::string> send_address(add_block_group, "txin", "Transaction input address.", {"txin", "send_address"});
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
        // std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e)
    {
        std::cerr << e.what() << std::endl;
        // std::cerr << parser;
        return 1;
    }
    std::string database_location = args::get(db_loc);
    std::string genesis_reward_address = args::get(coinbase_address);
    Blockchain primary_blockchain(HASH_DIFF, genesis_reward_address, database_location);
    if (add){
       std::cout<<"Add block selected."<<std::endl; 
    }
    if (delete_chain){
        std::cout<<"Delete chain selected."<<std::endl; 
    }
    // else if (command == "add_block" || command == "a")
    // dispatch.run_add_block();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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