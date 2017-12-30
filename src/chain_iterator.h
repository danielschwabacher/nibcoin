#include <string>
#include <iostream>
#include <vector>
#include "block.h"
#include <leveldb/db.h>

#ifndef CHAINITER_INC 
#define CHAINITER_INC

class BlockchainIterator{
    private: 
        leveldb::DB *iteration_database;
        leveldb::Iterator* blockchain_iterator; 
    public:
        BlockchainIterator(leveldb::DB *database);
        void print_all_kv();
};

#endif