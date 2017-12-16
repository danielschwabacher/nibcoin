#include "block.h"
#include <iostream>

int main(){
    // Genesis Block
    Block b(0, "blah block data");
    std::cout<<"Block hash is: "<<b.get_block_hash()<<std::endl;
    return 0;
}
