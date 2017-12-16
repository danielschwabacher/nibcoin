#include <string>
#include <iostream>

#ifndef BLOCK_INC
#define BLOCK_INC

/*
    A block is the main component of a blockchain.
    A block stores the following information:
    i.) data: arbitrary data which comprises a block
    ii.) previous_hash: the hash value of the block preceding this block in the chain
    iii.) block_hash: the hash value of the block
    iv.) timestamp: the time when the block is created
    
    Hashes are assumed to be integers. 
    Any nessecary casting is to be done in 
    these utility functions.

*/
class Block{
    private:
        std::time_t timestamp;
        std::string data;
        int previous_hash;
        int block_hash;
    public:
        Block(int prv_hash, std::string block_data);
        time_t get_timestamp();
        std::string get_data();
        int get_prev_hash();
        int get_block_hash();
        int set_hash();
};

#endif