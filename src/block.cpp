#include "block.h"
#include "proofer.h"
#include "../lib/sha256.h"
#include <string>
#include <ctime>
#include "../lib/json.hpp"


/*
    Standard block constructor, used when creating blocks based on 
    blocks that are found earlier in the chain.
*/
Block::Block(std::string prv_hash, std::string block_data){
    timestamp = std::time(nullptr);
    data = block_data;
    previous_hash = prv_hash;
    block_hash = set_hash();
}

/* 
    Genesis block constructor, ignore the previous hash.
*/
Block::Block(std::string block_data){
    timestamp = std::time(nullptr);
    data = block_data;
    previous_hash = "";
    block_hash = set_hash();
}

/* 
    Serializable block constructor, used when reconstructing blocks from JSON data
*/
Block::Block(std::time_t block_timestamp, std::string block_data, std::string prv_hash, std::string current_hash, int block_nonce){
    timestamp = block_timestamp;
    data = block_data;
    previous_hash = prv_hash;
    block_hash = current_hash;
    nonce = block_nonce;
}


/* 
    --- Getters for each Block attribute ---
*/
std::time_t Block::get_timestamp(){
    return timestamp;
}

std::string Block::get_data(){
    return data;
}

std::string Block::get_prev_hash(){
    return previous_hash;
}

std::string Block::get_block_hash(){
    return block_hash;    
}

int Block::get_nonce(){
    return nonce;
}

/*
    A block_hash is the hashed value of a block's
    timestamp + data + previous_hash
*/
std::string Block::set_hash(){
    std::string contents = std::to_string(timestamp) + data + previous_hash;
    std::string sha256_digest = sha256(contents);
    return sha256_digest;
}

/*
    Used to reset the block nonce once a valid nonce is found
*/
void Block::set_nonce(int valid_nonce){
    nonce = valid_nonce;
}

/*
    Used to reset the block hash once a provable hash is found
*/
void Block::reset_hash(std::string new_hash){
    block_hash = new_hash;
}
