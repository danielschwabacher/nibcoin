#include <string>
#include <iostream>
#include <vector>
#include "../lib/json.hpp"

#ifndef TX_INC
#define TX_INC

/*
*/
class TransactionOutput{
    private:
        int value;
        std::string public_key;
    public:
        TransactionOutput(int v, std::string pub_key);
        int get_tx_output_value();
        std::string get_tx_output_pubkey();
};

/*
*/
class TransactionInput{
    private:
        std::string tx_id;
        std::string script_signature;
        int vout;
    public:
        TransactionInput(std::string prev_output_txid, std::string sig, int v_index);
        std::string get_tx_input_id();
        std::string get_tx_input_script_signature();
        int get_tx_input_vout();
        void to_json(nlohmann::json& j, const TransactionInput& input_tx_to_serialize);
        void from_json(const nlohmann::json& j, TransactionInput& deserialize_input_tx);
};

/*
*/
class Transaction{
    private:
        std::string transaction_id;
        std::vector<TransactionInput> transaction_inputs;
        std::vector<TransactionOutput> transaction_outputs;
    public:
        // i.) Constructors
        Transaction();        
        Transaction(std::string id, TransactionInput input, TransactionOutput output);
        Transaction(std::string id, std::vector<TransactionInput> inputs, std::vector<TransactionOutput> outputs);
        // ii.) Genesis functionality
        Transaction new_coinbase_tx(std::string to, std::string data);
        // iii.) Getters
        std::string get_tx_string();
        std::vector<TransactionInput> get_tx_inputs();
        std::vector<TransactionOutput> get_tx_outputs();
        // iv.) Wrappers
        void print_tx_inputs();
        void print_tx_outputs();
        // v.) Possible serialization optimizations
        // void to_json(nlohmann::json& j, const Transaction& tx_to_serialize);
        // void from_json(const nlohmann::json& j, Transaction& tx_to_deserialize);
};

#endif
