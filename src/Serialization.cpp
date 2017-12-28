#include "Serialization.h"
#include "block.h"
#include <string>
#include "../lib/json.hpp"

SerializationWrapper::SerializationWrapper(){

}

/*
    Returns an object containing a 
    block's data serialized as JSON.
*/
nlohmann::json SerializationWrapper::serialize_block(Block block_to_serialize){
    nlohmann::json block_data;
    block_data["block_timestamp"] = block_to_serialize.get_timestamp();
    block_data["block_data"] = block_to_serialize.get_data();
    block_data["prv_hash"] = block_to_serialize.get_prev_hash();
    block_data["current_hash"] = block_to_serialize.get_block_hash();
    block_data["block_nonce"] = block_to_serialize.get_nonce();
    return block_data;
}


DeserializationWrapper::DeserializationWrapper(){
    
}

/*
    Returns a Block object constructed from 
    serialized JSON data.
*/
Block DeserializationWrapper::deserialize_block(nlohmann::json block_data){
    std::time_t current_block_time =  block_data["block_timestamp"];
    std::string current_block_data = block_data["block_data"];
    std::string current_previous_hash = block_data["prv_hash"];
    std::string current_block_hash = block_data["current_hash"];
    int current_nonce = block_data["block_nonce"];
    Block restored_block(current_block_time, current_block_data, current_previous_hash, current_block_hash, current_nonce);
    return restored_block;
}