#include "Serialization.h"
#include "block.h"
#include <string>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

SerializationWrapper::SerializationWrapper(){

}

int SerializationWrapper::demonstrate_serialization(){
    // 0.) File to write serialized data to
    std::ofstream ofs("/tmp/serial_test.dat");
    // 1.) Create a bogus, non-linked block to serialize
    Block test_block("previous", "random block data");
    {
        boost::archive::text_oarchive out_archive(ofs);
        out_archive << test_block;
    }
    return 0;
}

DeserializationWrapper::DeserializationWrapper(){
    
}

int DeserializationWrapper::demonstrate_deserialization(){
    // 0.) Open the serialized data
    std::ifstream ifs("/tmp/serial_test.dat");
    // 1.) Create a block which will hold the restored data  
    Block restored_block("s");
    {
        boost::archive::text_iarchive input_archive(ifs);
        input_archive >> restored_block;
    }
    std::cout<<"---Deserialized block data---"<<std::endl;
    std::cout<<"Block timestamp: "<<restored_block.get_timestamp()<<std::endl;        
    std::cout<<"Block data: "<<restored_block.get_data()<<std::endl;    
    return 0;
}