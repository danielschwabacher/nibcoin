#include "blockchain.h"

// const int TARGET_ZEROS = 4;
// const std::string database_location = "/tmp/blocks";

/*
    
*/
Blockchain::Blockchain(int leading_zeros, std::string db_loc) : blockchain_db(db_loc) {
    target_zeros = leading_zeros;
    db_location = db_loc;
    SerializationWrapper serializer = SerializationWrapper();
    if (!blockchain_db.check_genesis()){
        std::cout<<"No genesis block found, mining one..."<<std::endl;
        Block genesis_block = generate_genesis_block();
    }
    else{
        std::cout<<"Genesis block found"<<std::endl;
    }
    tip = blockchain_db.get_last_hash_value();
}


Block Blockchain::new_block(std::string data){
    Block spawn_block(tip, data);
    Proofer proof_of_work(&spawn_block, target_zeros);
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
    Proofer proof_of_work(&genesis_block, target_zeros);
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

std::string Blockchain::get_db_location(){
    return db_location;
}

Database Blockchain::get_database(){
    return blockchain_db;
}