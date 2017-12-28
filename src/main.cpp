#include "block.h"
#include "blockchain.h"
#include "Serialization.h"
#include "../lib/json.hpp"
#include <iostream>
#include <leveldb/db.h>


/*

*/
int main(){ 
    Blockchain primary_blockchain;
    primary_blockchain.new_block("First block");
    primary_blockchain.new_block("Second block");
    return 0;
}

