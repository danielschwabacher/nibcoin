#include "block.h"
#include "blockchain.h"
#include <iostream>

int main(){ 
    Blockchain primary_blockchain;
    primary_blockchain.add_block("Sent 1 things to Ron");
    primary_blockchain.add_block("Sent 2 things to Tyler");   
    primary_blockchain.add_block("Sent 6 things to Tyler");   
    primary_blockchain.add_block("Sent 2 things to Tyler");    
    primary_blockchain.print_blockchain();
    return 0;
}
