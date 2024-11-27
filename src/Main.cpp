#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "Emulator.hpp"
#include "Consts.hpp"
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "[ERROR] Usage : ./slc game.rom/game.ch8\n";
        std::cerr << "[ERROR] No ROM provided !\n";
        return EXIT_FAILURE;
    }

    std::string romPath = std::string(argv[1]);

    Emulator chip8Emulator;

    try {
        chip8Emulator.InitAudio();
        chip8Emulator.LoadROMFromFile(romPath);
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("SLC - Chip8VM by Yann BOYER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "[ERROR] Unable to initialize the window !\n";
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (!renderer) {
        std::cerr << "[ERROR] Unable to initialize the renderer !\n";
        return EXIT_FAILURE;
    }

    bool isRunning = true;

    uint8_t divCycles = 0;

    while (isRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    std::cout << "[INFO] Exiting...\n";
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    break;
                case SDL_KEYUP:
                    break;
                default: break;
            }
        }

        chip8Emulator.ExecuteInstruction();
        divCycles++;

        // Draw
        for (uint8_t y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
            for (uint8_t x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
                SDL_Rect pixel = { x * PIXEL_SCALE_FACTOR, y * PIXEL_SCALE_FACTOR, PIXEL_SCALE_FACTOR, PIXEL_SCALE_FACTOR };
                if (chip8Emulator.IsPixelOn(x, y))
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

                SDL_RenderFillRect(renderer, &pixel);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        if (divCycles == TIMER_CLOCK_DIVISION) {
            chip8Emulator.UpdateCPUTimers();
            divCycles = 0;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(CPU_CLOCK_DELAY));
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
