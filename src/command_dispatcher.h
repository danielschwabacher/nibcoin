#include <string>
#include <iostream>
#include <vector>
#include <leveldb/db.h>
#include "blockchain.h"
#include "block.h"

#ifndef CMD_DISPATCH 
#define CMD_DISPATCH

class CommandDispatcher{
    private:
        Blockchain *chain_context;
    public:
        CommandDispatcher(Blockchain *chain_context);    
        int run_add_block();
        int run_print_chain();
};

#endif