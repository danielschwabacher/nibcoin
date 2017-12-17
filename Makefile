CC=clang++
CFLAGS=-Wall -Wextra
MAINSOURCEDIR := ./src
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

all: blockchain

blockchain: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o blockchain.out

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm ./bin/blockchain

  # Below causes lnker errors \
block.o: $(MAINSOURCEDIR)/block.cpp \
	$(CC) $(CFLAGS) $(MAINSOURCEDIR)/block.cpp \
main.o: $(MAINSOURCEDIR)/main.cpp \
	$(CC) $(CFLAGS) $(MAINSOURCEDIR)/main.cpp \
	blockchain: $(MAINSOURCEDIR)/main.cpp $(MAINSOURCEDIR)/block.cpp $(MAINSOURCEDIR)/blockchain.cpp \
	$(CC) $(CCFLAGS) -o ./bin/blockchain $(MAINSOURCEDIR)/main.cpp $(MAINSOURCEDIR)/block.cpp $(MAINSOURCEDIR)/blockchain.cpp