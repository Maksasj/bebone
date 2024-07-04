#include "bebone/bebone.h"

#include <cstdio>

using namespace bebone::sound_system;

int main() {
    SoundEngine sound_engine;
    Sound coin_sound = sound_engine.load_sound("coin_sound.mp3");

    coin_sound.play();

    std::cout << "Press enter to exit...";

    getchar();

    return 0;
}
