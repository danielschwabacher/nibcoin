CC=clang++
CFLAGS=-Wall -Wextra
MAINSOURCEDIR := ./src
SOURCES = $(wildcard src/*.cpp lib/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

all: blockchain

blockchain: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o blockchain.out

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm blockchain.out
	rm ./bin/blockchain
	rm ./build/*.o