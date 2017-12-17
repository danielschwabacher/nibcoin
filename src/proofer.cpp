#include "block.h"
#include "proofer.h"
#include "../lib/sha256.h"
#include <string>

Proofer::Proofer(Block *block_to_prove, int zeros_target){
    pow_block_ptr = block_to_prove;
    target = zeros_target;
}

/*
    Returns a sha256 digest of the contents of an entire block.
*/
std::string Proofer::prepare_data(int nonce){
    std::string block_contents = std::to_string(pow_block_ptr->get_timestamp()) + pow_block_ptr->get_data() + pow_block_ptr->get_prev_hash() + pow_block_ptr->get_block_hash() + std::to_string(nonce);
    return block_contents;
}

