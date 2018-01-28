#include "block.h"

/*
    Standard block constructor, used when creating blocks based on 
    blocks that are found earlier in the chain.
*/
Block::Block(std::string prv_hash, Transaction txs) : transactions(txs){
    timestamp = std::time(nullptr);
    transactions = txs;
    previous_hash = prv_hash;
    block_hash = set_hash();
}

/* 
    Genesis block constructor, ignore the previous hash.
*/
Block::Block(Transaction txs) : transactions(txs){
    timestamp = std::time(nullptr);
    transactions = txs;
    previous_hash = "";
    block_hash = set_hash();
}

/*
    Serializable block constructor, used when reconstructing blocks from JSON data
*/
Block::Block(std::time_t block_timestamp, Transaction txs, std::string prv_hash, std::string current_hash, int block_nonce) : transactions(txs){
    timestamp = block_timestamp;
    transactions = txs;
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

Transaction Block::get_transactions(){
    return transactions;
}

std::string Block::get_prev_hash(){
    return previous_hash;
}

std::string Block::get_block_hash(){
    return block_hash;    
}

std::string Block::get_transaction_string(){
    return transactions.get_tx_string();    
}

int Block::get_nonce(){
    return nonce;
}

/*
    A block_hash is the hashed value of a block's
    timestamp + data + previous_hash
*/
std::string Block::set_hash(){
    std::string contents = std::to_string(timestamp) + transactions.get_tx_string() + previous_hash;
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

/*
Possible simplified way of serializing/deserializing
void Block::to_json(nlohmann::json& j, const Block& block_to_serialize){
    j = nlohmann::json{
        {"block_timestamp", block_to_serialize.timestamp},
        {"prv_hash", block_to_serialize.previous_hash},
        {"current_hash", block_to_serialize.block_hash},
        {"block_nonce", block_to_serialize.nonce},
        {"block_tx_data", block_to_serialize.transactions}
    };
}

void Block::from_json(const nlohmann::json& j, Block& deserialize_block){
    deserialize_block.timestamp = j.at("block_timestamp").get<time_t>();
    deserialize_block.previous_hash = j.at("prv_hash").get<std::string>();
    deserialize_block.block_hash = j.at("current_hash").get<std::string>();
    deserialize_block.nonce = j.at("block_nonce").get<int>();
    deserialize_block.transactions = j.at("block_tx_data").get<Transaction>();
}
*/