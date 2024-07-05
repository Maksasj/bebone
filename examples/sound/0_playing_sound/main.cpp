#include "bebone/bebone.h"

#include <cstdio>

using namespace bebone::sound_system;

int main() {
    SoundEngine sound_engine;

    auto sound = sound_engine.load_sound("coin_sound.mp3");
    sound->play();

    std::cout << "Press enter to exit...";
    getchar();

    sound_engine.load_sound("jump.mp3", sound);
    sound->play();

    std::cout << "Press enter to exit...";
    getchar();

    return 0;
}
