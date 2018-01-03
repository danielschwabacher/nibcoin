#include "database.h"
#include "Serialization.h"
#include <leveldb/db.h>
#include <fstream>



bool file_exists(std::string fileName){
    std::ifstream infile(fileName);
    return infile.good();
}

/*
    Create a new LevelDB database instance
*/
Database::Database(std::string db_loc){
    has_genesis = false;
    location = db_loc;
    if (file_exists(location)){
        has_genesis = true;
    }
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::DB::Open(options, db_loc, &database);
}

leveldb::DB* Database::get_database(){
    return database;
}

bool Database::check_genesis(){
    return has_genesis;
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

/*

*/
int Database::write_block(Block block_to_write){
    SerializationWrapper serializer = SerializationWrapper();    
    nlohmann::json block_data = serializer.serialize_block(block_to_write);
    std::string hash = block_data["current_hash"];
    std::string hash_of_last_block = block_data["current_hash"];
    std::string data_string  = block_data.dump();
    database->Put(leveldb::WriteOptions(), hash, data_string);
    database->Put(leveldb::WriteOptions(), "l", hash_of_last_block);
    has_genesis = true;
    return 0;
}
