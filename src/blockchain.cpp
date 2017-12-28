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
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/test_blockchain_db", &blockchain_db);
    assert(status.ok());
    Block genesis_block = generate_genesis_block();
    SerializationWrapper serial;
    nlohmann::json serialized_block_data = serial.serialize_block(genesis_block);
    blockchain_db->Put(leveldb::WriteOptions(), serialized_block_data.dump(), "Genesis block");
}
/*
void Blockchain::print_blockchain(){
    std::cout<<"Blocks in this blockchain"<<std::endl;
    std::cout<<"----------------"<<std::endl;                        
    for (size_t i = 0; i < blocks_vector.size(); i++){
        Block current_block = blocks_vector[i];
        std::cout<<"Previous hash: "<<current_block.get_prev_hash()<<std::endl;
        std::cout<<"Block data: "<<current_block.get_data()<<std::endl;
        std::cout<<"Block hash: "<<current_block.get_block_hash()<<std::endl;            
        std::cout<<"----------------"<<std::endl;                    
    }
}

int Blockchain::get_number_blocks(){
    return number_of_blocks;
}


Block Blockchain::new_block(std::string data){
    std::string previous_block_hash = blocks_vector[blocks_vector.size() - 1].get_block_hash();
    Block spawn_block(previous_block_hash, data);
    Proofer proof_of_work(&spawn_block, TARGET_ZEROS);
    std::pair<int, std::string> pow_results = proof_of_work.run_pow();
    // Reset block nonce to contain a valid nonce
    spawn_block.set_nonce(std::get<0>(pow_results));
    // Reset the block hash to the valid hash 
    spawn_block.reset_hash(std::get<1>(pow_results));
    blocks_vector.push_back(spawn_block);
    number_of_blocks++;
    return spawn_block;
}
*/
Block Blockchain::generate_genesis_block(){
    Block genesis_block("0", "Genesis block");
    Proofer proof_of_work(&genesis_block, TARGET_ZEROS);
    std::pair<int, std::string> pow_results = proof_of_work.run_pow();
    // Reset block nonce to contain a valid nonce
    genesis_block.set_nonce(std::get<0>(pow_results));
    // Reset the block hash to the valid hash 
    genesis_block.reset_hash(std::get<1>(pow_results));
    // blocks_vector.push_back(genesis_block);
    // number_of_blocks++;
    return genesis_block;
}