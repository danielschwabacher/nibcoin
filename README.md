
# nibcoin
nibcoin is an experimental, simple cryptocurrency currently in development. It aims to be the simplest minimum viable cryptocurrency. Though there are currently no actual nibcoin tokens floating around, this repository contains a locally buildable nibcoin implementation, which can demonstrate (locally) some of the core functionality of nibcoin.

# Usage
nibcoin is only tested on macOS. The following instructions can be utilized to build nibcoin-core and demonstrate (again, locally) some of the nibcoin blockchain functionality. In its current state, the local versions of nibcoin-core require some familiarity with the underpinnings of cryptocurrencies. It will be helpful to understand the basics of Bitcoin or a similar coin before messing around with the current version of nibcoin. 

0.) **Dependencies (make sure these are installed first)**

* [LevelDB](https://github.com/google/leveldb)

* [Snappy libraries](https://github.com/google/snappy)
* [Boost serialization libraries](http://www.boost.org/)

1.) Make the project 
* `make`

2.) Run the executable
* `./blockchains.out`
* This will show an extensive help menu, then exit

3.) Create a nibcoin blockchain 
* `./blockchains.out create --db=<location> --address=<reward address>`
* Creates a new nibcoin blockchain and genesis block. Once mined the reward will be given to the address specified by the reward address
* the `create` command creates a levelDB directory at the location specified. All of the other nibcoin commands take an argument specifying which blockchain directory to modify. 

4.) "Send" some coins (these commands will reflect themselves in the levelDB file, but do not actually do anything currently)
* `add --address=<Transaction input> --amount=<Number of coins to send> --database=<Database file location>`
* Adds a new block to the blockchain specified in the database argument. 

5.) View the chain
 * `./blockchains.out print --database=<Database file location>`
	 * Nicely print out the blockchain data contained in the database argument
 * `./blockchains.out dump --database=<Database file location>`
	 * Dump the raw blockchain data contained in the database argument

6.) Delete chains
 * `./blockchains.out delete --database=<Database file location>`
* Safely delete the levelDB artifacts
# Technical Details
**These are not final and subject to change throughout development.** 
Proof-of-work: modified version of **HashCash**
Hashing algorithm: **SHA-256**
Internal database: **levelDB**
Total number of coins: **TBD**

# Roadmap
Basic blockchain ✅

Proof of work ✅

Transactions and addresses 🚧

Network

Windows support

Linux support

Alias addresses

# License
This project falls under the [unlicense](http://unlicense.org/). It is in the public domain and you can use it for whatever you want, without restriction or attribution. 

