#include "block.h"
#include "blockchain.h"
#include <iostream>

int main(){ 
    Blockchain primary_blockchain;   
    primary_blockchain.new_block("First block");
    primary_blockchain.new_block("Seoncd block");
    primary_blockchain.new_block("Third block");
    primary_blockchain.print_blockchain();    
    return 0;
}
