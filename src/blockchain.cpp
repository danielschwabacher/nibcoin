#include "blockchain.h"
#include "block.h"
#include "proofer.h"
#include "database.h"
#include "Serialization.h"
#include "../lib/json.hpp"
#include <string>
#include <cassert>

const int TARGET_ZEROS = 2;
const std::string database_location = "/tmp/blocks";

/*
    
*/
Blockchain::Blockchain() : blockchain_db(database_location) {
    // blockchain_db = Database(database_location);
    SerializationWrapper serializer = SerializationWrapper();
    if (!blockchain_db.check_genesis()){
        std::cout<<"No genesis block found, mining one..."<<std::endl;
        Block genesis_block = generate_genesis_block();
    }
    else{
        std::cout<<"Genesis block found"<<std::endl;
    }
}


Block Blockchain::new_block(std::string data){
    Block spawn_block(tip, data);
    Proofer proof_of_work(&spawn_block, TARGET_ZEROS);
    std::pair<int, std::string> pow_results = proof_of_work.run_pow();
    // Reset block nonce to contain a valid nonce
    spawn_block.set_nonce(std::get<0>(pow_results));
    // Reset the block hash to the valid hash 
    spawn_block.reset_hash(std::get<1>(pow_results));
    SerializationWrapper serial;
    nlohmann::json serialized_block_data = serial.serialize_block(spawn_block);
    tip = spawn_block.get_block_hash();
    blockchain_db.write_block(spawn_block);
    return spawn_block;
}

Block Blockchain::generate_genesis_block(){
    Block genesis_block("Genesis block");
    Proofer proof_of_work(&genesis_block, TARGET_ZEROS);
    std::pair<int, std::string> pow_results = proof_of_work.run_pow();
    // Reset block nonce to contain a valid nonce
    genesis_block.set_nonce(std::get<0>(pow_results));
    // Reset the block hash to the valid hash 
    genesis_block.reset_hash(std::get<1>(pow_results));
    SerializationWrapper serial;
    nlohmann::json serialized_block_data = serial.serialize_block(genesis_block);
    blockchain_db.write_block(genesis_block);
    tip = genesis_block.get_block_hash();
    return genesis_block;
}

Database Blockchain::get_database(){
    return blockchain_db;
}