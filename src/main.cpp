#include <iostream>
#include <algorithm>
#include <leveldb/db.h>
#include <stdlib.h>

#include "command_dispatcher.h"
#include "../lib/args.hxx"

const int HASH_DIFF = 3;

void CreateCommand(args::Subparser &parser)
{
    args::Group create_group(parser, "", args::Group::Validators::AllOrNone); 
    args::ValueFlag<std::string> coinbase_address(create_group, "coinbase_address", "The address which will recieve the mining reward upon validation of the genesis block.", {"coinbase_address", "coinbase", "address"});
    args::ValueFlag<std::string> db_loc(create_group, "database", "The LevelDB file which will store the blockchain data.", {"database", "db"});
    parser.Parse();
    if (!coinbase_address){
        std::cout<<"Missing coinbase address"<<std::endl;        
        std::cout<<"Usage: create --address=<Reward Address> --database=<Database file location>"<<std::endl;
        return;
    }
    if (!db_loc){
        std::cout<<"Missing database location"<<std::endl;        
        std::cout<<"Usage: create --address=<Reward Address> --database=<Database file location>"<<std::endl;
        return;
    }
    std::string database_location = args::get(db_loc);
    std::string genesis_reward_address = args::get(coinbase_address);
    Blockchain primary_blockchain(HASH_DIFF, genesis_reward_address, database_location);
}

void AddCommand(args::Subparser &parser)
{
    args::Group add_block_group(parser, "", args::Group::Validators::AllOrNone);
    args::ValueFlag<std::string> send_address(add_block_group, "txin", "Transaction input address.", {"txin", "send_address"});
    args::ValueFlag<std::string> num_coins(add_block_group, "num_coins", "The number of coins to send.", {"num_coins", "coins"});
    args::ValueFlag<std::string> database_add_block(add_block_group, "database", "The LevelDB file to update upon completion.", {"database", "db"});
    parser.Parse();
    if (!send_address){
        std::cout<<"Missing send address"<<std::endl;
        std::cout<<"Usage: add --txin=<Transaction input> --coins=<Number of coins to send> --database=<Database file location>"<<std::endl;
        return;
    }
    if (!num_coins){
        std::cout<<"Missing coins"<<std::endl;
        std::cout<<"Usage: add --txin=<Transaction input> --coins=<Number of coins to send> --database=<Database file location>"<<std::endl;
        return;
    }
    if (!database_add_block){
        std::cout<<"Missing database"<<std::endl;
        std::cout<<"Usage: add --txin=<Transaction input> --coins=<Number of coins to send> --database=<Database file location>"<<std::endl;
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
}

/*
    This is mostly just bootstrapping the command line interface. 
*/
int main(int argc, char** argv){ 
    args::ArgumentParser parser("Blockchain CLI.", "");
    args::Group commands(parser, "Commands");
    // Handles creating a new blockchain
    args::Command create(commands, "create", "Create a new blockchain, given an initial address and database file. Usage: create --address=<Reward Address> --database=<Database file location>", &CreateCommand);        
    // Handles adding a block to the blockchain
    args::Command add(commands, "add", "Adds a dummy block to the chain containing arbritrary transaction data. Usage: add --txin=<Transaction input> --coins=<Number of coins to send> --database=<Database file location>", &AddCommand);
    // Handles deleting blockchain levelDB files
    args::Command delete_chain(commands, "delete", "Safely deletes a blockchain LevelDB directory and associated data.", &DeleteCommand);
    // Handles deleting blockchain levelDB files
    args::Command print(commands, "print", "Safely deletes a blockchain LevelDB directory and associated data.", &PrintCommand);
    // Handles deleting blockchain levelDB files
    args::Command dump(commands, "dump", "Safely deletes a blockchain LevelDB directory and associated data.", &DumpCommand);
    
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