CC=clang++ -std=c++14
CFLAGS=-Wall -Wextra

# Boost headers location and libraries to link against
BOOSTHEADERS=-I /usr/local/boost-1.66.0/include
BOOSTLIBDIR=/usr/local/boost-1.66.0/lib/libboost_serialization.a

MAINSOURCEDIR := ./src



SOURCES = $(wildcard src/*.cpp lib/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

all: blockchain

blockchain: $(OBJECTS)
	$(CC) $(CFLAGS) $(BOOSTHEADERS) $(OBJECTS) -o blockchain.out $(BOOSTLIBDIR)

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(BOOSTHEADERS) -c $< -o $@
	
clean:
	rm blockchain.out
	rm ./build/*.o