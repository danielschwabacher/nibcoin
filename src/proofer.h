
#include <string>
#include <iostream>
#include <vector>
#include "block.h"
#include <tuple>
#ifndef PROOF_INC 
#define PROOF_INC

/*
    Proofers are the main proof of work (PoW) system.
    A Proofer puzzle is considered solved when a nonce is 
    found such that, when applied to the hashed value
    of an entire block, begins with at least as many 
    zeros as the zero target.
*/

class Proofer{
    private:
        Block *pow_block_ptr;
        int target;
    public:
        Proofer(Block *block_to_prove, int zeros_target);
        std::string prepare_data(int nonce);
};
#endif