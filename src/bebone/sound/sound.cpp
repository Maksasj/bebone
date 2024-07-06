#include "sound.h"

namespace bebone::sound_system {
    Sound::Sound() : loaded_sound(nullptr) { }
    Sound::~Sound() {
        free();
    }

    void Sound::play() {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_start(raw);
    }

    void Sound::stop() {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_stop(raw);
    }

    void Sound::rewind() {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_seek_to_pcm_frame(raw, 0);
    }

    void Sound::free() {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_uninit(raw);
        loaded_sound = nullptr;
    }

    ma_sound* Sound::get_raw_sound() {
        return loaded_sound.get();
    }
}