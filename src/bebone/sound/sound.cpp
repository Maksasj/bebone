#include "sound.h"

namespace bebone::sound_system {
    Sound::Sound() : loaded_sound(nullptr) { }
    Sound::~Sound() {
        free();
    }

    void Sound::play() {
        ma_sound* raw = loaded_sound.get();
        ma_sound_start(raw);
    }

    void Sound::free() {
        ma_sound* raw = loaded_sound.get();

        if (raw != nullptr) {
            ma_sound_uninit(raw);
        }
    }
}