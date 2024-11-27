slc is a basic Chip8 Emulator written in C++ with SDL2.



Building(you'll need GCC/Clang + SDL2 & SDL2_mixer on Linux) :



cmake -B build -DCMAKE_BUILD_TYPE=Release -GNinja

ninja -C build -j1

cp build/slc .

./slc roms/your_rom_of_choice.ch8



Copyright (c) 2024 - Yann BOYER.
