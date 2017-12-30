#include "block.h"
#include "blockchain.h"
#include "Serialization.h"
#include "chain_iterator.h"
#include "../lib/json.hpp"
#include <iostream>
#include <leveldb/db.h>


/*

*/
int main(){ 
    Blockchain primary_blockchain;
    primary_blockchain.new_block("First block");
    primary_blockchain.new_block("Second block");
    leveldb::DB *primary_database = primary_blockchain.get_database();
    BlockchainIterator printer(primary_database);
    printer.print_all_kv();
    return 0;
}

