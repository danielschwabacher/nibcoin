#include "blockchain.h"
#include "block.h"
#include "proofer.h"
#include "Serialization.h"
#include "../lib/json.hpp"
#include <string>
#include <cassert>
#include <leveldb/db.h>

const int TARGET_ZEROS = 2;

/*
    
*/
Blockchain::Blockchain(){
    leveldb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = false;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/blocks", &blockchain_db);
    assert(status.ok());
    Block genesis_block = generate_genesis_block();
    tip = genesis_block.get_block_hash();
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
    blockchain_db->Put(leveldb::WriteOptions(), data, serialized_block_data.dump());
    tip = spawn_block.get_block_hash();
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
    blockchain_db->Put(leveldb::WriteOptions(), "Genesis block", serialized_block_data.dump());
    return genesis_block;
}

leveldb::DB* Blockchain::get_database(){
    return blockchain_db;
}
