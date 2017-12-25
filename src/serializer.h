#include <string>
#include <iostream>


#ifndef SERIALIZER_INC
#define SERIALIZER_INC

/*
    A Serializer is responsible for encoding block data
    into a format compatible with the data storage protocol.
    The main function, serialize, accepts a block and returns
    that block's data as a byte array.
*/
class Serializer{
    public:
        Serializer();
        std::string serialize(Block block_to_serialize);
};

/*
    A Deserializer is responsible for decoding block data
    bytes into a format compatible with the data storage protocol.
    The main function, deserialize, accepts an arbtiray byte stream 
    and returns the corresponding block.
*/
class Deserializer{
    public:
        Deserializer();
        // std::string deserialize();
};

#endif