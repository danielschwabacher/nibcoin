#include <string>
#include <iostream>
#include <vector>
#include "block.h"
#include <leveldb/db.h>

#ifndef BLOCKCHAIN_INC 
#define BLOCKCHAIN_INC

/*
*/
class Blockchain{
    private:
        leveldb::DB *blockchain_db;
        // last block hash in DB
        std::string tip;
    public:
        Blockchain();        
        void print_blockchain();
        int get_number_blocks();
        Block new_block(std::string data);
        Block generate_genesis_block();
};

#endif