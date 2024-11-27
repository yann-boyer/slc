#include "Memory.hpp"
#include <iostream>

Memory::Memory() {
    m_memory.fill(0x0);
}

void Memory::Write(uint16_t addr, uint8_t value) {
    if (addr > MEMORY_SIZE - 1) {
        std::cerr << "[ERROR] Memory Error : WRITE command is out of range !\n";
        std::exit(1);
    }

    m_memory[addr] = value;
}

uint8_t Memory::Read(uint16_t addr) {
    if (addr > MEMORY_SIZE - 1) {
        std::cerr << "[ERROR] Memory Error : READ command is out of range !\n";
        std::exit(1);
    }

    return m_memory[addr];
}
