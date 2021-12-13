#include "MemoryControl.h"
#include <random>

void readFirst(int n, int div, MemoryControl* mem, std::uint64_t range) {
    
    
    std::uint64_t R_address = 0x0000000000000000;

    std::uint64_t W_address = 0x3000000000000000;
    
    std::uint64_t ByteRange = range * 1024;
    std::uint64_t CacheLine = 64;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint64_t> dis(0, ByteRange);

    for (int i = 0; i < 32 ;i++) {
        cout << i << '\n';
        while(!mem->AddTransaction(R_address, READ)) {
            mem->UpdateCycle();
        }
        R_address += CacheLine;
        cout << "done\n";
    }
}

void writeFirst(int n, int div, MemoryControl* mem) {
    std::uint64_t R_address = 0x0000000000000000;
    std::uint64_t W_address = 0x3000000000000000;
    std::uint64_t CacheLineByte = 64;
    int cnt = div;
    while (cnt--) {
        for (int i = 0; i < n/div; i++) {
            while(!mem->AddTransaction(W_address, WRITE)) {
                mem->UpdateCycle();
            }
            W_address += CacheLineByte;
        }
        for (int i = 0; i < n/div; i++) {
            while(!mem->AddTransaction(R_address, READ)) {
                mem->UpdateCycle();
            }
            R_address += CacheLineByte;
        }
    }
}

int main(int argc, char** argv) {
    // [ n ] [ div ] [ mode ]
    int n = atoi(argv[1]);
    int div = atoi(argv[2]);
    int range = atoi(argv[3]);

    MemoryControl* mem = new MemoryControl("/home/jeehyun/memInit/src/DRAMsim3/configs/DDR4_8Gb_x16_3200.ini", "/home/jeehyun/memInit/trace");
    
    readFirst(n, div, mem, range);

    while(mem->read_num < 32) {
        mem->UpdateCycle();
    }
    mem->PrintStats();
    delete(mem);
}
