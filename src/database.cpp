#include "database.h"
#include <leveldb/db.h>


/*
    Create a new LevelDB database instance
*/
Database::Database(std::string db_loc){
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::DB::Open(options, db_loc, &database);
}

int Database::write_data(std::string key, std::string value){
    database->Put(leveldb::WriteOptions(), key, value);    
    return 0;
}

std::string Database::get_data(std::string key){
    std::string value;
    database->Get(leveldb::ReadOptions(), key, &value);    
    return value;
}