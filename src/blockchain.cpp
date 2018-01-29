#include "blockchain.h"

// const int TARGET_ZEROS = 4;
// const std::string database_location = "/tmp/blocks";

/*
    
*/
Blockchain::Blockchain(int leading_zeros, std::string reward_address, std::string db_loc) : blockchain_db(db_loc) {
    target_zeros = leading_zeros;
    db_location = db_loc;
    SerializationWrapper serializer = SerializationWrapper();
    if (!blockchain_db.check_genesis()){
        std::string genesis_reward_addr;
        std::cout<<"No genesis block found here!"<<std::endl;
        Block genesis_block = generate_genesis_block(reward_address);
        std::cout<<"Created a new blockchain, initial reward address: "<<reward_address<<std::endl;
        std::cout<<"Blockchain data file can be found in: "<<db_loc<<std::endl;
    }
    else{
        std::cout<<"Genesis block found, not taking any further action."<<std::endl;
    }
    tip = blockchain_db.get_last_hash_value();
}

Block Blockchain::new_block(Transaction txs){
    Block spawn_block(tip, txs);
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

Block Blockchain::generate_genesis_block(std::string gen_reward_addr){
    Transaction coinbase_tx_holder;
    Transaction cb_tx = coinbase_tx_holder.new_coinbase_tx(gen_reward_addr, "Coinbase TX");
    Block genesis_block(cb_tx);
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