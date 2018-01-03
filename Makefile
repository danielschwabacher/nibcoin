# Build flags to pass into Clang
CC=clang++ -std=c++14
CFLAGS=-Wall -Wextra

# Boost headers location and libraries to link against
BOOST_HEADERS=-I /usr/local/boost-1.66.0/include
BOOST_SERIAL_LIB_DIR=/usr/local/boost-1.66.0/lib/libboost_serialization.a

# LevelDB headers and library location
LEVELDB_LIB_DIR=/usr/local/Cellar/leveldb/1.19/lib/libleveldb.a
LEVELDB_HEADERS=-I /usr/local/Cellar/leveldb/1.19/include

# Snappy headers and lib location: LevelDB dependency
SNAPPY_LIB_DIR=/usr/local/Cellar/snappy/1.1.3/lib/libsnappy.a
SNAPPY_HEADERS=-I /usr/local/Cellar/snappy/1.1.3/include

# Wildcards to build everything in the src/ directory 
MAINSOURCEDIR := ./src
SOURCES = $(wildcard src/*.cpp lib/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

all: blockchain

blockchain: $(OBJECTS)
	$(CC) $(CFLAGS) $(BOOST_HEADERS) $(LEVEL_DB_HEADERS) $(OBJECTS) -o blockchain.out $(BOOST_SERIAL_LIB_DIR) $(LEVELDB_LIB_DIR) $(SNAPPY_LIB_DIR)

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(BOOST_HEADERS) $(LEVELDB_HEADERS) $(SNAPPY_HEADERS) -c $< -o $@
	
clean:
	rm blockchain.out
	rm ./build/*.o
	rm -rf /tmp/blocks