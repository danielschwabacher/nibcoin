#include <string>
#include <iostream>
#include <vector>
#include "block.h"

#ifndef BLOCKCHAIN_INC 
#define BLOCKCHAIN_INC

/*
*/
class Blockchain{
    private:
        std::vector<Block> blocks_vector;
        int number_of_blocks;
    public:
        Blockchain();        
        void print_blockchain();
        int add_block(Block block_to_add);
        int get_number_blocks();
};

#endif