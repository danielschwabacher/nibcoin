#include "blockchain.h"
#include <string>
#include <ctime>


Blockchain::Blockchain(){
    std::cout<<"Blockchain created!"<<std::endl;
    number_of_blocks = 0;
}

void Blockchain::print_blockchain(){
    std::cout<<"Things is blockchain"<<std::endl;
}

int Blockchain::add_block(Block block_to_add){
    blocks_vector.push_back(block_to_add);
    number_of_blocks++;
    return 0;
}
int Blockchain::get_number_blocks(){
    return number_of_blocks;
}