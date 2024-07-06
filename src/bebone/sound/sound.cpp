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
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_seek_to_pcm_frame(raw, 0);
    }

    void Sound::set_volume(const float& volume) {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_volume(raw, volume);
    }

    void Sound::set_pan(const float& pan) {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_pan(raw, pan);
    }

    void Sound::set_pitch(const float& pitch) {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_pitch(raw, pitch);
    }

    void Sound::set_looping(const bool& loop) {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_looping(raw, loop);
    }

    bool Sound::is_playing() {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return false;
        }

        ma_sound* raw = get_raw_sound();
        return ma_sound_is_playing(raw);
    }

    bool Sound::at_end() {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return false;
        }

        ma_sound* raw = get_raw_sound();
        return ma_sound_at_end(raw);
    }

    bool Sound::is_looping() {
        if (loaded_sound == nullptr) {
            // TODO: throw a warning
            return false;
        }

        ma_sound* raw = get_raw_sound();
        return ma_sound_is_looping(raw);
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