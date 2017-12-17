#include "block.h"
#include "proof_of_work.h"
#include "../lib/sha256.h"
#include <string>
#include <ctime>


Block::Block(std::string prv_hash, std::string block_data){
    timestamp = std::time(nullptr);
    data = block_data;
    previous_hash = prv_hash;
    block_hash = set_hash();
}


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