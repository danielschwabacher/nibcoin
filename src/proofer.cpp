#include "block.h"
#include "proofer.h"
#include "../lib/sha256.h"
#include <bitset>  
#include <string>


Proofer::Proofer(Block *block_to_prove, int zeros_target){
    pow_block_ptr = block_to_prove;
    target = zeros_target;
}

/*
    Build and return a string containing all of a block's information plus a nonce.
*/
std::string Proofer::prepare_data(int nonce){
    std::string block_contents = std::to_string(pow_block_ptr->get_timestamp()) + pow_block_ptr->get_data() + pow_block_ptr->get_prev_hash() + pow_block_ptr->get_block_hash() + std::to_string(nonce);
    return block_contents;
}

// A valid hash has target leading zeros. 
int Proofer::run_pow(){
    std::cout << "Running PoW..." << std::endl;
    int nonce = 0;
    int maxNone = 20;
    // Convert this to the bit represenation of a sha256 hash (0xFFFFFFFF) -> (11111111111111111111111111111111)
    int hash_repr;
    std::string hash;
    std::string hash_substring;
    while (nonce < maxNone){
        std::string block_data = prepare_data(nonce);
        hash = sha256(block_data);
        hash_substring = hash.substr(0, target);
        hash_repr = std::stoi(hash_substring, 0, 16);
        std::cout << "Hash substring: " << hash_repr << std::endl;        
        if (hash_repr == target){
            std::cout<<"Valid nonce and hash found!"<<std::endl;
            std::cout<<"Hash is: "<< hash << std::endl;
            std::cout<<"Nonce is: "<< nonce << std::endl;
            return 0;
        }
        else{
            nonce++;
        }
    }
    return 0;
}