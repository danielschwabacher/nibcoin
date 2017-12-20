#include "block.h"
#include "proofer.h"
#include "../lib/sha256.h"
#include <bitset>  
#include <string>

/*
    The following PoW algoritihm is based on Hashcash. To prove a block has done the nessecary amount of work 
    before being added to the blockchain, it needs to determined a nonce, such that when added alongside the hashed 
    contents of a block generates the specified amount of target zeros. Higher target zero values take more computational 
    power and time, as it becomes increasingly unlikely that any given nonce will generate many leading zeros in the SHA-256 digest. 
*/


/*
    block_to_prove is the relevant block which a Proofer object will generate a nonce for.
    zeros_target is how many leading zeros should be seen when generating hash(block_to_prove + nonce)
*/
Proofer::Proofer(Block *block_to_prove, int zeros_target){
    pow_block_ptr = block_to_prove;
    target = zeros_target;
}

/*
    Helper function for run_pow()
    Given a string, returns true if every character in the string is a zero.
*/
bool Proofer::is_valid_substring(std::string hex_substring){
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

/*
    This returns a valid nonce for a block, trying up to (2^63 - 1) nonces. It works in the following manner:
    1.) Prepare the block data
    2.) Generate a SHA256 digest of the block data
    3.) Slice off the leading target_zeros substring from the hash digest.
    4.) Check if that substring is all zeros.
        4.1) If yes, return nonce and hash.
        4.2 If no, increment the nonce value and try again
*/
int Proofer::run_pow(){
    int nonce = 0;
    int maxNone = 200;
    std::string hash;
    std::string hash_substring;
    while (nonce < maxNone){
        std::string block_data = prepare_data(nonce);
        hash = sha256(block_data);
        // Pull the target number of leading chars
        hash_substring = hash.substr(0, target);
        if (is_valid_substring(hash_substring)){
            std::cout<<"VALID HASH FOUND: "<<hash<<std::endl;
            std::cout<<"NONCE: "<<nonce<<std::endl;
            return nonce;
        }
        nonce++;
    }
    return 0;
}


