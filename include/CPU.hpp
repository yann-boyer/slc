#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <array>
#include <vector>
#include "Audio.hpp"
#include "Memory.hpp"
#include "RenderTable.hpp"

enum class KeyState {
    Pressed,
    NotPressed,
};

class CPU {
    public:
        CPU();

        void SetKey(uint8_t n, bool isDown);
        void UpdateTimers(AudioPlayer& audioPlayer);
        void ExecuteInstruction(Memory& memory, RenderTable& renderTable);
    private:
        uint16_t FetchNextOpcode(Memory& memory);

        static constexpr uint8_t REGISTERS_COUNT = 16;
        static constexpr uint8_t KEYS_COUNT=  16;

        std::array<uint8_t, REGISTERS_COUNT> m_registers;
        std::vector<uint16_t> m_stack;
        std::array<KeyState, KEYS_COUNT> m_keys;

        uint16_t m_indexRegister;
        uint8_t m_delayTimer;
        uint8_t m_soundTimer;
        uint16_t m_programCounter;
};

#endif
