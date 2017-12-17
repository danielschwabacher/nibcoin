#include "block.h"
#include "blockchain.h"
#include <iostream>

int main(){
    Blockchain primary_blockchain;
    primary_blockchain.add_block("Sent 1 nibcoin to Ron");
    primary_blockchain.add_block("Sent 2 nibcoins to Tyler");   
    primary_blockchain.add_block("Sent 6 nibcoins to Tyler");   
    primary_blockchain.add_block("Sent 2 nibcoins to Tyler");    
    primary_blockchain.print_blockchain();
    return 0;
}
