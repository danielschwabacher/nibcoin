#include <string>
#include <iostream>
#include <vector>
#include <leveldb/db.h>

#include "block.h"
#include "blockchain.h"
#include "Serialization.h"

#include "../lib/json.hpp"

#ifndef CHAINITER_INC 
#define CHAINITER_INC

class BlockchainIterator{
    private: 
        leveldb::DB *iteration_database;
        leveldb::Iterator* blockchain_iterator; 
    public:
        BlockchainIterator(leveldb::DB *database);
        void print_all_kv();
        void pretty_print();
};

#endif