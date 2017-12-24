CC=clang++ -std=c++11
CFLAGS=-Wall -Wextra
LEVELDBHEADERS=-I /usr/local/Cellar/leveldb/1.19/include
MAINSOURCEDIR := ./src
SOURCES = $(wildcard src/*.cpp lib/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

all: blockchain

blockchain: $(OBJECTS)
	$(CC) $(CFLAGS) $(LEVELDBHEADERS) $(OBJECTS) -o blockchain.out 

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(LEVELDBHEADERS) -c $< -o $@
	
clean:
	rm blockchain.out
	rm ./bin/blockchain
	rm ./build/*.o