#include "sound.h"

namespace bebone::sound_system {
    Sound::Sound() : loaded_sound(nullptr) { }
    Sound::~Sound() {
        ma_sound* raw = loaded_sound.get();
        ma_sound_uninit(raw);
    }

    void Sound::play() {
        ma_sound* raw = loaded_sound.get();
        ma_sound_start(raw);
    }
}