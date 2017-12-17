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
*/
class Block{
    private:
        std::time_t timestamp;
        std::string data;
        std::string previous_hash;
        std::string block_hash;
    public:
        Block(std::string prv_hash, std::string block_data);
        Block(std::string block_data);
        std::time_t get_timestamp();
        std::string get_data();
        std::string get_prev_hash();
        std::string get_block_hash();
        std::string set_hash();
};

#endif