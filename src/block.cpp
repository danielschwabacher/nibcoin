#include "block.h"
#include <string>
#include <ctime>


Block::Block(int prv_hash, std::string block_data){
    timestamp = std::time(nullptr);
    data = block_data;
    previous_hash = prv_hash;
    block_hash = set_hash();
}
/* 
    --- Getters for each Block attribute ---
*/
time_t Block::get_timestamp(){
    return timestamp;
}

std::string Block::get_data(){
    return data;
}

int Block::get_prev_hash(){
    return previous_hash;
}

int Block::get_block_hash(){
    return static_cast<int>(block_hash);    
}
/*
    A block_hash is the hashed value of a new block's
    timestamp + data + previous_hash
*/
int Block::set_hash(){
    std::string contents = std::to_string(timestamp) + data + std::to_string(previous_hash);
    return static_cast<int>(std::hash<std::string>()(contents));
}