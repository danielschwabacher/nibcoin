#include "blockchain.h"
#include "block.h"
#include "Serialization.h"
#include "../lib/json.hpp"
#include "chain_iterator.h"
#include <string>
#include <leveldb/db.h>


/*
    BlockchainIterator is responsible for returning the relevant 
    blocks in a blockchain. 
*/
BlockchainIterator::BlockchainIterator(leveldb::DB *database){
    iteration_database = database;
    blockchain_iterator = iteration_database->NewIterator(leveldb::ReadOptions());
}


void BlockchainIterator::print_all_kv(){
    for (blockchain_iterator->SeekToFirst(); blockchain_iterator->Valid(); blockchain_iterator->Next()){
        std::cout << blockchain_iterator->key().ToString() << ": "  << blockchain_iterator->value().ToString() << std::endl;
    }
}
