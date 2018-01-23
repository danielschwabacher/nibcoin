#include "transaction.h"

const int SUBSIDY = 10;

Transaction::Transaction(){
    std::vector<TransactionInput> inputs_vector;
    std::vector<TransactionOutput> outputs_vector;
    transaction_id = "cb";
    transaction_inputs = inputs_vector;
    transaction_outputs = outputs_vector;
}

/*
*/
Transaction::Transaction(std::string id, std::vector<TransactionInput> inputs, std::vector<TransactionOutput> outputs){
    transaction_id = id;
    transaction_inputs = inputs;
    transaction_outputs = outputs;
}


std::string Transaction::get_tx_string(){
    return transaction_id;
}


TransactionOutput::TransactionOutput(int v, std::string pub_key){
    value = v;
    public_key = pub_key;
}

TransactionInput::TransactionInput(std::string prev_output_txid, std::string sig, int v_index){
    tx_id = prev_output_txid;
    script_signature = sig;
    vout = v_index;
}


Transaction Transaction::new_coinbase_tx(std::string to, std::string data){
    TransactionInput txin("null", data, -1);
    TransactionOutput txout(SUBSIDY, to);
    std::vector<TransactionInput> inputs_vector;
    std::vector<TransactionOutput> outputs_vector;
    inputs_vector.push_back(txin);
    outputs_vector.push_back(txout);
    static Transaction cb_transaction = Transaction("coinbase_tx", inputs_vector, outputs_vector);
    return cb_transaction;
}