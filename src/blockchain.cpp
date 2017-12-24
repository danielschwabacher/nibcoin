#include "blockchain.h"
#include "block.h"
#include "leveldb/db.h"
#include "proofer.h"
#include <string>
#include <ctime>
#include <tuple>

const int TARGET_ZEROS = 4;

Blockchain::Blockchain(){
    number_of_blocks = 0;
    generate_genesis_block();
    std::cout<<"Blockchain created!"<<std::endl;
}

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

Block Blockchain::generate_genesis_block(){
    Block genesis_block("Genesis block");
    Proofer proof_of_work(&genesis_block, TARGET_ZEROS);
    std::pair<int, std::string> pow_results = proof_of_work.run_pow();
    // Reset block nonce to contain a valid nonce
    genesis_block.set_nonce(std::get<0>(pow_results));
    // Reset the block hash to the valid hash 
    genesis_block.reset_hash(std::get<1>(pow_results));
    blocks_vector.push_back(genesis_block);
    number_of_blocks++;
    return genesis_block;
}