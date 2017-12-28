#include <string>
#include <iostream>
#include "block.h"
#include "../lib/json.hpp"

#ifndef SERIALIZER_INC
#define SERIALIZER_INC

/*
    A SerializationWrapper provides wrappers to 
    serialize across different data types.
*/
class SerializationWrapper{
    public:
        SerializationWrapper();
        nlohmann::json serialize_block(Block block_to_serialize);
};

/*
    A DeserializationWrapper provides wrappers to 
    deserialize across different data types.
*/
class DeserializationWrapper{
    public:
        DeserializationWrapper();
        Block deserialize_block(nlohmann::json json_data);      
};

#endif