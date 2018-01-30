#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <leveldb/db.h>

#include "blockchain.h"
#include "chain_iterator.h"
#include "block.h"
#include "database.h"
#include "serialization.h"
#include "transaction.h"
#include "proofer.h"

#include "../lib/json.hpp"


#ifndef CMD_DISPATCH 
#define CMD_DISPATCH

class CommandDispatcher{
    private:
        Blockchain *chain_context;
    public:
        CommandDispatcher(Blockchain *chain_context);    
        int run_add_block(int amount, std::string send_addr);
        int run_dump_chain();
        int run_delete_chain();
        int run_pretty_print();
        int print_help();
};

#endif