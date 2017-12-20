#include "block.h"
#include "proofer.h"
#include "../lib/sha256.h"
#include <bitset>  
#include <string>


Proofer::Proofer(Block *block_to_prove, int zeros_target){
    pow_block_ptr = block_to_prove;
    target = zeros_target;
}

// Returns true if the target number of leading characters are all zeros.
bool is_valid_substring(std::string hex_substring){
    for (int i = 0; i < hex_substring.length(); i++){
        if (hex_substring[i] == '0'){}
        else{
            return false;
        }
    }
    return true;
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
    int nonce = 0;
    int maxNone = 20;
    std::string hash;
    std::string hash_substring;
    while (nonce < maxNone){
        std::string block_data = prepare_data(nonce);
        hash = sha256(block_data);
        // std::cout << "Hash string: " << hash << std::endl;
        // pull the target number of leading chars
        hash_substring = hash.substr(0, target);
        if (is_valid_substring(hash_substring)){
            std::cout<<"VALID HASH FOUND: "<<hash<<std::endl;
            std::cout<<"NONCE: "<<nonce<<std::endl;
        }
        nonce++;
    }
    return 0;
}


