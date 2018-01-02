#include <string>
#include <iostream>
#include <leveldb/db.h>

#ifndef DATABASE_INC
#define DATABASE_INC

/*
*/
class Database{
    private:
        leveldb::DB* database;
    public:
        Database(std::string db_loc);
        int write_data(std::string key, std::string value);
        std::string get_data(std::string key);
};
#endif