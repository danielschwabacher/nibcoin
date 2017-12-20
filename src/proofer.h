
#include <string>
#include <iostream>
#include <vector>
#include "block.h"
#include <tuple>
#ifndef PROOF_INC 
#define PROOF_INC

class Proofer{
    private:
        Block *pow_block_ptr;
        int target;
    public:
        Proofer(Block *block_to_prove, int zeros_target);
        std::string prepare_data(int nonce);
        bool is_valid_substring(std::string hex_substring);            
        int run_pow();
};

#endif