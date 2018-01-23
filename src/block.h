#include <string>
#include <iostream>
#include <ctime>

#include "transaction.h"

#include "../lib/json.hpp"
#include "../lib/sha256.h"


#ifndef BLOCK_INC
#define BLOCK_INC

/*
    A block is the main component of a blockchain.
    A block stores the following information:
    i.) data: arbitrary data which comprises a block
    ii.) previous_hash: the hash value of the block preceding this block in the chain
    iii.) block_hash: the hash value of the block
    iv.) timestamp: the time when the block is created
    v.) nonce: a number which, when applied to a certain contents to be hashed, satisfies the proof of work (PoW) puzzle.
*/
class Block{
    private:
        std::time_t timestamp;
        Transaction transactions;
        std::string previous_hash;
        std::string block_hash;
        int nonce;
    public:
        Block(std::string prv_hash, Transaction txs);
        Block(Transaction txs);
        Block(std::time_t block_timestamp, Transaction txs, std::string prv_hash, std::string current_hash, int block_nonce);            
        std::time_t get_timestamp();
        Transaction get_transactions();
        std::string get_transaction_string();
        std::string get_prev_hash();
        std::string get_block_hash();
        int get_nonce();
        std::string set_hash();
        void reset_hash(std::string new_hash);
        void set_nonce(int valid_nonce);
};
#endif