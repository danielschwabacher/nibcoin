#include "blockchain.h"
#include "block.h"
#include "proofer.h"
#include <string>
#include <ctime>


Blockchain::Blockchain(){
    number_of_blocks = 0;
    add_block("Genesis block");
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

int Blockchain::add_block(std::string block_data){
    if (blocks_vector.size() > 0){
        Block previous_block = blocks_vector[blocks_vector.size() - 1];
        Block block_to_add = Block(previous_block.get_block_hash(), block_data);
        blocks_vector.push_back(block_to_add);
        number_of_blocks++; 
        return 0;
    }
    // Genesis block case
    else {
        Block genesis_block = Block(block_data);
        blocks_vector.push_back(genesis_block);
        number_of_blocks++; 
        return 1;
    }
    return -1;
}

int Blockchain::get_number_blocks(){
    return number_of_blocks;
}


Block Blockchain::new_block(std::string data){
    int target_zeros = 1;
    std::string previous_block_hash = blocks_vector[blocks_vector.size() - 1].get_prev_hash();
    Block spawn_block(previous_block_hash, data);
    Proofer proof_of_work(&spawn_block, target_zeros);
    proof_of_work.run_pow();
    return spawn_block;
}