#include "Emulator.hpp"
#include <fstream>
#include <iostream>

void Emulator::InitAudio() {
    m_audioPlayer.Init();
}

void Emulator::LoadROMFromFile(const std::string& romPath) {
    std::ifstream romFile(romPath, std::ios::binary);

    if (!romFile.is_open())
        throw std::runtime_error("[ERROR] Unable to open the ROM !");

    std::vector<uint8_t> romBuffer;

    romFile.seekg(0, std::ios::end);
    std::size_t romBufferSize = romFile.tellg();
    romFile.seekg(0, std::ios::beg);

    if (romBufferSize > MAX_ROM_SIZE - 1)
        throw std::runtime_error("[ERROR] This ROM is too large to fit into the memory !");

    romBuffer.reserve(romBufferSize);
    romFile.read(reinterpret_cast<char*>(romBuffer.data()), romBufferSize);
    romFile.close();

    // Load FONTSET before anything else.
    for (uint8_t i = 0; i < FONTSET_SIZE; i++) {
        m_memory.Write(i, FONTSET[i]);
    }

    for (std::size_t bufIndex = 0; bufIndex < romBufferSize; bufIndex++) {
        m_memory.Write(PROCESSOR_INTERNAL_PROGRAM_COUNTER_START + bufIndex, romBuffer[bufIndex]);
    }

    std::cout << "[INFO] ROM successfully loaded into memory !\n";
}

bool Emulator::IsPixelOn(uint8_t x, uint8_t y) {
    return m_renderTable.IsPixelOn(x, y);
}

void Emulator::UpdateCPUTimers() {
    m_cpu.UpdateTimers(m_audioPlayer);
}

void Emulator::ExecuteInstruction() {
    m_cpu.ExecuteInstruction(m_memory, m_renderTable);
}
