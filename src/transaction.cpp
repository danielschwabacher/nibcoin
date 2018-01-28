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

/*
    Constructor for single Inputs and Outputs. Automatically populates the TX vectors with these values.
*/
Transaction::Transaction(std::string id, TransactionInput input, TransactionOutput output){
    transaction_id = id;
    transaction_inputs.push_back(input); 
    transaction_outputs.push_back(output);
};


std::string Transaction::get_tx_string(){
    return transaction_id;
}

// Simplifies printing the inputs and ouputs
void Transaction::print_tx_inputs(){
    std::cout << "TRANSCATION INPUTS" << std::endl;
    for(auto i : transaction_inputs){
        std::cout << "TX ID: " << i.get_tx_input_id() << std::endl;
        std::cout << "Script signature: " << i.get_tx_input_script_signature() << std::endl;
        std::cout << "TX ID: " << i.get_tx_input_vout() << std::endl;
    } 
}



void Transaction::print_tx_outputs(){
    return;
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


TransactionOutput::TransactionOutput(int v, std::string pub_key){
    value = v;
    public_key = pub_key;
}




TransactionInput::TransactionInput(std::string prev_output_txid, std::string sig, int v_index){
    tx_id = prev_output_txid;
    script_signature = sig;
    vout = v_index;
}


/*
    Getters for TransactionInput
*/
std::string TransactionInput::get_tx_input_id(){
    return tx_id;
}

std::string TransactionInput::get_tx_input_script_signature(){
    return script_signature;
}

int TransactionInput::get_tx_input_vout(){
    return vout;
}
