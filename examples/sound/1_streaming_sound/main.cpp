#include "bebone/bebone.h"

#include <cstdio>

using namespace bebone::sound_system;

int main() {
    SoundEngine sound_engine;
    auto factory = std::make_shared<StreamSoundFactory>();

    auto sound = sound_engine.load_sound("Dungeon Master.wav", factory);
    sound->play();

    std::cout << "Press enter to exit...";
    getchar();

    return 0;
}
