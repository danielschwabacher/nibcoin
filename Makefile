CC=clang++
CFLAGS=-Wall -Wextra
MAINSOURCEDIR=./src
all: blockchain

blockchain: $(MAINSOURCEDIR)/main.cpp $(MAINSOURCEDIR)/block.cpp
	$(CC) $(CCFLAGS) -o ./bin/blockchain $(MAINSOURCEDIR)/main.cpp $(MAINSOURCEDIR)/block.cpp

# Below causes lnker errors \
block.o: $(MAINSOURCEDIR)/block.cpp \
	$(CC) $(CFLAGS) $(MAINSOURCEDIR)/block.cpp \
main.o: $(MAINSOURCEDIR)/main.cpp \
	$(CC) $(CFLAGS) $(MAINSOURCEDIR)/main.cpp \
	
clean:
	rm ./bin/blockchain