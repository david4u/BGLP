#ifndef __MEMORYCONTROL_H__
#define __MEMORYCONTROL_H__

#include "Common.h"
#include <src/dramsim3.h>
#include <queue>

class MemoryControl {
public:
    MemoryControl(const std::string& config_file, const std::string& output_dir);
    ~MemoryControl();
    void UpdateCycle();
    bool AddTransaction(std::uint64_t address, bool is_write);
    void PrintStats();
    void ClockTick();
    int write_num;
    int read_num;

private:
    dramsim3::MemorySystem *mem;

    void ReadCompleteCallback(std::uint64_t address);
    void WriteCompleteCallback(std::uint64_t address);
    };

#endif