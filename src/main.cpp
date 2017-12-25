#include "block.h"
#include "blockchain.h"
#include <iostream>
#include <fstream>

int main(){ 
    Blockchain primary_blockchain;   
    primary_blockchain.new_block("First block");
    primary_blockchain.new_block("Second block");
    primary_blockchain.new_block("Third block");
    primary_blockchain.print_blockchain();    
    
    Block test_block("previous", "hello");

    std::ofstream ofs("/tmp/filename.dat", std::ios::binary);
    {
        boost::archive::binary_oarchive oa(ofs);
        oa << test_block;
    }

    {
      std::ifstream file{"/tmp/filename.dat"};
      boost::archive::binary_iarchive ia(file);
      Block other_block("s");
      ia >> other_block;
      std::cout << "Deserialized block has previous hash: " << other_block.get_prev_hash() << '\n';      
      std::cout << "Deserialized block is: " << other_block.get_data() << '\n';
    }



    return 0;
}
