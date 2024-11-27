#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <array>

class Memory {
    public:
        Memory();

        void Write(uint16_t addr, uint8_t value);
        uint8_t Read(uint16_t);
    private:
        // 4096 bytes of RAM.
        static constexpr uint16_t MEMORY_SIZE = 4096;

        std::array<uint8_t, MEMORY_SIZE> m_memory;
};

#endif
