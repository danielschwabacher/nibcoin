#include "block.h"
#include "proofer.h"
#include "../lib/sha256.h"
#include <string>
#include <ctime>


Block::Block(std::string prv_hash, std::string block_data){
    timestamp = std::time(nullptr);
    data = block_data;
    previous_hash = prv_hash;
    block_hash = set_hash();
}

/* 
    This is a makeshift genesis block constructor, it contains an empty string for the previous hash.
*/
Block::Block(std::string block_data){
    timestamp = std::time(nullptr);
    data = block_data;
    previous_hash = "";
    block_hash = set_hash();
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

/*
    A block_hash is the hashed value of a new block's
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


void Block::reset_hash(std::string new_hash){
    block_hash = new_hash;
}