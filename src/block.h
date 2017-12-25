#include <string>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const int version)
        {
            ar & timestamp;
            ar & data;
            ar & previous_hash;
            ar & block_hash;
            ar & nonce;
        }
        std::time_t timestamp;
        std::string data;
        std::string previous_hash;
        std::string block_hash;
        int nonce;
    public:
        Block(std::string prv_hash, std::string block_data);
        Block(std::string block_data);
        std::time_t get_timestamp();
        std::string get_data();
        std::string get_prev_hash();
        std::string get_block_hash();
        int get_nonce();
        std::string set_hash();
        void reset_hash(std::string new_hash);
        void set_nonce(int valid_nonce);
};

#endif