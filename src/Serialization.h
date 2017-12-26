#include <string>
#include <iostream>
#include "block.h"
#include <fstream>

#ifndef SERIALIZER_INC
#define SERIALIZER_INC

/*
    A SerializationWrapper provides a few handy wrappers to 
    test serialization functionality across different data types.
*/
class SerializationWrapper{
    public:
        SerializationWrapper();
        int demonstrate_serialization();
};

/*
    A DeserializationWrapper provides a few handy wrappers to 
    test deserialization functionality across different data types.
*/
class DeserializationWrapper{
    public:
        DeserializationWrapper();
        int demonstrate_deserialization();        
};

#endif