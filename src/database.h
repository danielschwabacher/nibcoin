#include "block.h"
#include <string>
#include <iostream>
#include <leveldb/db.h>
#include "../lib/json.hpp"

#ifndef DATABASE_INC
#define DATABASE_INC

/*
*/
class Database{
    private:
        leveldb::DB* database;
        bool has_genesis;
        std::string location;
    public:
        Database(std::string db_loc);
        leveldb::DB* get_database();
        bool check_genesis();
        int write_data(std::string key, std::string value);
        std::string get_data(std::string key);
        int write_block(Block block_to_write);
};
#endif

