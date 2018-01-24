#include <string>
#include <iostream>
#include <vector>

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
};

/*
*/
class Transaction{
    private:
        std::string transaction_id;
        std::vector<TransactionInput> transaction_inputs;
        std::vector<TransactionOutput> transaction_outputs;
    public:
        Transaction();        
        Transaction(std::string id, TransactionInput input, TransactionOutput output);
        Transaction(std::string id, std::vector<TransactionInput> inputs, std::vector<TransactionOutput> outputs);
        // A coinbase TX only has input
        Transaction new_coinbase_tx(std::string to, std::string data);
        std::string get_tx_string();
};

#endif
