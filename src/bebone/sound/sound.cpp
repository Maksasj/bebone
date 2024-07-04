#include "sound.h"

namespace bebone::sound_system {
    Sound::Sound() : loaded_sound(nullptr) { }
    Sound::~Sound() {
        ma_sound_uninit(loaded_sound);
    }

    void Sound::play() {
        ma_sound_start(loaded_sound);
    }
}