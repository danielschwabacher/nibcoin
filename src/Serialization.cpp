#include "serialization.h"

SerializationWrapper::SerializationWrapper(){

}

/*
    Returns an object containing a 
    block's data serialized as JSON.
*/
nlohmann::json SerializationWrapper::serialize_block(Block block_to_serialize){
    nlohmann::json block_data;
    Transaction block_transaction = block_to_serialize.get_transactions();
    TransactionInput block_tx_input = block_transaction.get_tx_inputs()[0];
    TransactionOutput block_tx_output = block_transaction.get_tx_outputs()[0];
    block_data["block_timestamp"] = block_to_serialize.get_timestamp();
    // block_data["block_data"] = block_to_serialize.get_data();
    block_data["prv_hash"] = block_to_serialize.get_prev_hash();
    block_data["current_hash"] = block_to_serialize.get_block_hash();
    block_data["block_nonce"] = block_to_serialize.get_nonce();
    block_data["block_tx_id"] = block_transaction.get_tx_string();
    block_data["block_tx_inputs_id"] = block_tx_input.get_tx_input_id();
    block_data["block_tx_inputs_script_sig"] = block_tx_input.get_tx_input_script_signature();
    block_data["block_tx_inputs_vout"] = block_tx_input.get_tx_input_vout();
    block_data["block_tx_output_value"] = block_tx_output.get_tx_output_value();
    block_data["block_tx_output_pubkey"] = block_tx_output.get_tx_output_pubkey();
    return block_data;
}


DeserializationWrapper::DeserializationWrapper(){
    
}

/*
    Returns a Block object constructed from 
    serialized JSON data.
*/
Block DeserializationWrapper::deserialize_block(nlohmann::json block_data){
    // Deserialization for Blocks
    std::time_t current_block_time =  block_data["block_timestamp"];
    std::string current_previous_hash = block_data["prv_hash"];
    std::string current_block_hash = block_data["current_hash"];
    int current_nonce = block_data["block_nonce"];

    // Deserialization for TransactionInputs
    std::string tx_id = block_data["block_tx_id"];
    std::string tx_script_sig = block_data["block_tx_inputs_script_sig"];
    int tx_vout = block_data["block_tx_inputs_vout"];
    
    // Deserialization for TransactionOutputs
    int tx_val = block_data["block_tx_output_value"];
    std::string pubkey = block_data["block_tx_output_pubkey"];

    // Patch to get serialization working, does not preserve actual block data.
    TransactionInput txin(tx_id, tx_script_sig, tx_vout);
    TransactionOutput txout(tx_val, pubkey);
    
    // std::vector<TransactionInput> inputs_vector;
    // std::vector<TransactionOutput> outputs_vector;
    
    // inputs_vector.push_back(txin);
    // outputs_vector.push_back(txout);

    Transaction restored_tx = Transaction(tx_id, txin, txout);
    Block restored_block(current_block_time, restored_tx, current_previous_hash, current_block_hash, current_nonce);
    return restored_block;
}