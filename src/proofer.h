#include <string>
#include <iostream>
#include <vector>
#include <bitset>  
#include <tuple>
#include <climits>

#include "block.h"

#include "../lib/sha256.h"

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
        std::pair<int, std::string> run_pow();
};

#endif