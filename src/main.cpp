#include <iostream>
#include <algorithm>
#include <leveldb/db.h>
#include <stdlib.h>

#include "command_dispatcher.h"
#include "../lib/args.hxx"

const int HASH_DIFF = 3;


bool verify_file(std::string fileName){
    std::ifstream infile(fileName);
    return infile.good();
}

CommandDispatcher generate_dispatch(std::string db_file_location){
    Blockchain context(HASH_DIFF, "ignore", db_file_location);
    return CommandDispatcher(&context);
}

void CreateCommand(args::Subparser &parser)
{
    args::Group create_group(parser, "", args::Group::Validators::AllOrNone); 
    args::ValueFlag<std::string> coinbase_address(create_group, "coinbase_address", "The address which will recieve the mining reward upon validation of the genesis block.", {"coinbase"});
    args::ValueFlag<std::string> db_loc(create_group, "database", "The LevelDB file which will store the blockchain data.", {"database", "db"});
    parser.Parse();
    if (!coinbase_address){
        std::cout<<"Missing coinbase address"<<std::endl;        
        std::cout<<"Usage: create --coinbase=<Reward Address> --database=<Database file location>"<<std::endl;
        return;
    }
    if (!db_loc){
        std::cout<<"Missing database location"<<std::endl;        
        std::cout<<"Usage: create --coinbase=<Reward Address> --database=<Database file location>"<<std::endl;
        return;
    }
    std::string database_location = args::get(db_loc);
    std::string genesis_reward_address = args::get(coinbase_address);
    Blockchain primary_blockchain(HASH_DIFF, genesis_reward_address, database_location);
}

void AddCommand(args::Subparser &parser)
{
    args::Group add_block_group(parser, "", args::Group::Validators::AllOrNone);
    args::ValueFlag<std::string> send_address(add_block_group, "txin", "Transaction input address.", {"address"});
    args::ValueFlag<std::string> num_coins(add_block_group, "num_coins", "The number of coins to send.", {"amount"});
    args::ValueFlag<std::string> database_add_block(add_block_group, "database", "The LevelDB file to update upon completion.", {"database", "db"});
    parser.Parse();
    if (!send_address){
        std::cout<<"Missing send address"<<std::endl;
        std::cout<<"Usage: add --address=<Transaction input> --amount=<Number of coins to send> --database=<Database file location>"<<std::endl;
        return;
    }
    if (!num_coins){
        std::cout<<"Missing coins"<<std::endl;
        std::cout<<"Usage: add --address=<Transaction input> --amount=<Number of coins to send> --database=<Database file location>"<<std::endl;
        return;
    }
    if (!database_add_block){
        std::cout<<"Missing database"<<std::endl;
        std::cout<<"Usage: add --address=<Transaction input> --amount=<Number of coins to send> --database=<Database file location>"<<std::endl;
        return;
    }
}

void DeleteCommand(args::Subparser &parser)
{
    args::Group delete_group(parser, "", args::Group::Validators::AllOrNone);
    args::ValueFlag<std::string> database_delete(delete_group, "database", "The LevelDB file to delete.", {"database", "db"});    
    parser.Parse();
    if (!database_delete){
        std::cout<<"Missing database"<<std::endl;
        std::cout<<"Usage: delete --database=<Database file location>"<<std::endl;
        return;
    }
    std::string db_loc = args::get(database_delete);    
    if (verify_file(db_loc)){
        Blockchain context(db_loc);
        CommandDispatcher current_dispatch(&context);
        current_dispatch.run_delete_chain();
    }
    else{
        std::cout<<"Invalid database location, no database found in: "<<db_loc<<std::endl;        
    }

}

void PrintCommand(args::Subparser &parser)
{
    args::Group print_group(parser, "", args::Group::Validators::AllOrNone);
    args::ValueFlag<std::string> database_print(print_group, "database", "The LevelDB file to print out.", {"database", "db"});
    parser.Parse();
    if (!database_print){
        std::cout<<"Missing database"<<std::endl;
        std::cout<<"Usage: print --database=<Database file location>"<<std::endl;
        return;
    }
    
    std::string db_loc = args::get(database_print);
    if (verify_file(db_loc)){
        Blockchain context(db_loc);
        CommandDispatcher current_dispatch(&context);
        current_dispatch.run_pretty_print();
    }
    else{
        std::cout<<"Invalid database location, no database found in: "<<db_loc<<std::endl;
    }
}

void DumpCommand(args::Subparser &parser)
{
    args::Group dump_group(parser, "", args::Group::Validators::AllOrNone);
    args::ValueFlag<std::string> database_dump(dump_group, "database", "The LevelDB file to dump out.", {"database", "db"});
    parser.Parse();
    if (!database_dump){
        std::cout<<"Missing database"<<std::endl;
        std::cout<<"Usage: dump --database=<Database file location>"<<std::endl;
        return;
    }
    std::string db_loc = args::get(database_dump);    
    if (verify_file(db_loc)){
        Blockchain context(db_loc);
        CommandDispatcher current_dispatch(&context);
        current_dispatch.run_dump_chain();
    }
    else{
        std::cout<<"Invalid database location, no database found in: "<<db_loc<<std::endl;
    }
}

/*
    This is mostly just bootstrapping the command line interface. 
*/
int main(int argc, char** argv){ 
    args::ArgumentParser parser("Blockchain CLI.", "");

    args::Group commands(parser, "Commands");
    args::Group arguments(parser, "Arguments");
    args::ValueFlag<std::string> coinbase_address(arguments, "coinbase_address", "The address which will recieve the mining reward upon validation of the genesis block.", {"coinbase"});
    args::ValueFlag<std::string> send_address(arguments, "txin", "Transaction input address.", {"address"});
    args::ValueFlag<std::string> num_coins(arguments, "num_coins", "The number of coins to simulate sending.", {"amount"});
    args::ValueFlag<std::string> database(arguments, "database", "The LevelDB file to act upon.", {"database", "db"});

    // Handles creating a new blockchain
    args::Command create(commands, "create", "Create a new blockchain, given an initial address and database file. Usage: create --address=<Reward Address> --database=<Database file location>", &CreateCommand);        
    // Handles adding a block to the blockchain
    args::Command add(commands, "add", "Adds a dummy block to the chain containing arbritrary transaction data. Usage: add --txin=<Transaction input> --coins=<Number of coins to send> --database=<Database file location>", &AddCommand);
    // Handles deleting blockchain levelDB files
    args::Command delete_chain(commands, "delete", "Safely deletes a blockchain LevelDB directory and associated data. Usage: delete --database=<Database file location>", &DeleteCommand);
    // Handles pretty printing blockchain levelDB files
    args::Command print(commands, "print", "Nicely prints out blockchain LevelDB data. Usage: print --database=<Database file location>", &PrintCommand);
    // Handles dumping blockchain key/values from levelDB files
    args::Command dump(commands, "dump", "Raw dump of the key/values stored in the blockchain LevelDB file. Usage: dump --database=<Database file location>", &DumpCommand);
    
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
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
    return 0;
}