#include "block.h"
#include "blockchain.h"
#include "Serialization.h"
#include <iostream>
#include <leveldb/db.h>

int main(){ 
    Blockchain primary_blockchain;   
    primary_blockchain.new_block("First block");
    primary_blockchain.new_block("Second block");
    primary_blockchain.new_block("Third block");
    primary_blockchain.print_blockchain();
    SerializationWrapper serial;
    DeserializationWrapper deserial;
    serial.demonstrate_serialization();
    deserial.demonstrate_deserialization();
    // ----------------
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    if (status.ok()){
        std::cout<<"Database is okay"<<std::endl;
    }
    return 0;
}
