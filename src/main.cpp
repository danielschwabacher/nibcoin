#include "block.h"
#include "blockchain.h"
#include "Serialization.h"
#include <iostream>
#include <leveldb/db.h>

int main(){ 
    Blockchain primary_blockchain;
    Block test_block("previous_hash", "random_block_data");
    SerializationWrapper serial;
    DeserializationWrapper deserial;
    nlohmann::json serialized_block_data = serial.serialize_block(test_block);
    std::cout<<"JSON data is: "<<serialized_block_data<<std::endl;
    Block restored_block = deserial.deserialize_block(serialized_block_data);
    std::cout<<"Restored block DATA is: "<<restored_block.get_data()<<std::endl;
    std::cout<<"Restored block TIMESTAMP is: "<<restored_block.get_timestamp()<<std::endl;
    std::cout<<"Restored block PREVIOUS HASH is: "<<restored_block.get_prev_hash()<<std::endl;
    std::cout<<"Restored block BLOCK HASH is: "<<restored_block.get_block_hash()<<std::endl;
    return 0;
}

