#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <leveldb/db.h>

#include "block.h"
#include "database.h"
#include "serialization.h"
#include "proofer.h"

#include "../lib/json.hpp"



#ifndef BLOCKCHAIN_INC 
#define BLOCKCHAIN_INC

/*
*/
class Blockchain{
    private:
        Database blockchain_db;
        // last block hash in DB
        std::string tip;
        int target_zeros;
        std::string db_location;
    public:
        Blockchain(int leading_zeros, std::string db_loc);        
        Block new_block(std::string data);
        Block generate_genesis_block();
        Database get_database();
        std::string get_db_location();
};

#endif