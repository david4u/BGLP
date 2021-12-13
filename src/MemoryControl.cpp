#include "MemoryControl.h"

std::queue<uint64_t> acc_wq;

std::vector<Transaction> r_table;

std::uint64_t r_count = 0;
std::uint64_t write_count = 0;

MemoryControl::MemoryControl(const std::string& config_file, const std::string& output_dir) {
    mem = dramsim3::GetMemorySystem(config_file,
                                    output_dir,
                                    std::bind(&MemoryControl::ReadCompleteCallback, this, std::placeholders::_1),
                                    std::bind(&MemoryControl::WriteCompleteCallback, this, std::placeholders::_1));
    this->read_num = 0;
    this->write_num = 0;
}

MemoryControl::~MemoryControl() {
    delete mem;
}

void MemoryControl::UpdateCycle() {
    mem->ClockTick();
    // DRAMsim3 clock tick -> up cycle
    // DRAMsim3 where?
}

bool MemoryControl::AddTransaction(std::uint64_t address, bool is_write) {
    Transaction t;
    t.address = address;
    t.is_write = is_write;
    switch(is_write) {
        case WRITE:
            if (mem->WillAcceptTransaction(t.address, t.is_write)) {
                mem->AddTransaction(t.address, t.is_write);
                return true;
            }
        case READ:
            if (mem->WillAcceptTransaction(t.address, t.is_write)) {
                mem->AddTransaction(t.address, t.is_write);
                return true;
            }
    }
    return false;
}

void MemoryControl::ReadCompleteCallback(std::uint64_t address) {
    read_num++;
}

void MemoryControl::WriteCompleteCallback(std::uint64_t address) {
    write_num++;
}

void MemoryControl::PrintStats() {
    mem->PrintStats();
    std::cout << "read complete call back : " << this->read_num << '\n';
    std::cout << "write complete call back : " << this->write_num << '\n';
}