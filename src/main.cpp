#include "block.h"
#include "blockchain.h"
#include <iostream>

int main(){
    // Genesis Block
    Block b(0, "blah block data");
    Block b2(1, "blah block data");
    // std::cout<<"Block hash is: "<<b.get_block_hash()<<std::endl;
    Blockchain primary_blockchain;
    primary_blockchain.add_block(b);
    primary_blockchain.add_block(b2);
    std::cout<<"There are: "<<primary_blockchain.get_number_blocks()<<" blocks in this chain."<<std::endl;
    return 0;
}
