#include "chain_iterator.h"

/*
    BlockchainIterator is responsible for returning or displaying 
    the relevant blocks in a blockchain. 
*/
BlockchainIterator::BlockchainIterator(leveldb::DB *database){
    iteration_database = database;
    blockchain_iterator = iteration_database->NewIterator(leveldb::ReadOptions());
}


/*
    Print every key/value pair stored in the LevelDB database.
*/
void BlockchainIterator::print_all_kv(){
    for (blockchain_iterator->SeekToFirst(); blockchain_iterator->Valid(); blockchain_iterator->Next()){
        std::cout << blockchain_iterator->key().ToString() << ": "  << blockchain_iterator->value().ToString() << std::endl;
    }
    return;
}

/*
    Nicely display the objects in the block chain. 
    Note: expensive for long chains, reconstructs 
    each block in the chain and then pulls relevant data from them
*/
void BlockchainIterator::pretty_print(){
    DeserializationWrapper deserial = DeserializationWrapper();
    nlohmann::json json_block_data;
    std::cout << "Blockchain Data" << std::endl;
    for (blockchain_iterator->SeekToFirst(); blockchain_iterator->Valid(); blockchain_iterator->Next()){
        if (blockchain_iterator->key().ToString() != "l"){
            std::cout<<"------------------------"<<std::endl;
            std::cout<<"Block: "<<blockchain_iterator->key().ToString()<<std::endl;
            json_block_data = nlohmann::json::parse(blockchain_iterator->value().ToString());
            Block restored = deserial.deserialize_block(json_block_data);
            std::cout<<"Block data: " << restored.get_data() << std::endl;
            std::cout<<"Block timestamp: " << restored.get_timestamp() << std::endl;
            std::cout<<"Block nonce: " << restored.get_nonce() << std::endl;
            std::cout<<"Block previous hash: " << restored.get_prev_hash() << std::endl;
        }
    }
    std::cout<<"------------------------"<<std::endl;    
    std::cout<<"END OF CHAIN"<<std::endl;
    return;
}