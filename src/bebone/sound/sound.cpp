#include "sound.h"

namespace bebone::sound_system {
    Sound::Sound() : loaded_sound(nullptr) { }
    Sound::~Sound() {
        free();
    }

    void Sound::play() const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to play not loaded sound");
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_start(raw);
    }

    void Sound::stop() const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to stop not loaded sound");
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_stop(raw);
    }

    void Sound::rewind() const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to rewind not loaded sound");
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_seek_to_pcm_frame(raw, 0);
    }

    void Sound::set_volume(const float& volume) const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to set volume to not loaded sound");
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_volume(raw, volume);
    }

    void Sound::set_pan(const float& pan) const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to set pan to not loaded sound");
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_pan(raw, pan);
    }

    void Sound::set_pitch(const float& pitch) const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to set pitch to not loaded sound");
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_pitch(raw, pitch);
    }

    void Sound::set_looping(const bool& loop) const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to set looping to not loaded sound");

            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_set_looping(raw, loop);
    }

    bool Sound::is_playing() const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to check is sound playing on not loaded sound");
            // TODO: throw a warning
            return false;
        }

        ma_sound* raw = get_raw_sound();
        return ma_sound_is_playing(raw);
    }

    bool Sound::at_end() const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to check is sound ending on not loaded sound");
            // TODO: throw a warning
            return false;
        }

        ma_sound* raw = get_raw_sound();
        return ma_sound_at_end(raw);
    }

    bool Sound::is_looping() const {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to check is sound looping on not loaded sound");
            // TODO: throw a warning
            return false;
        }

        ma_sound* raw = get_raw_sound();
        return ma_sound_is_looping(raw);
    }

    void Sound::free() {
        if (loaded_sound == nullptr) {
            LOG_WARNING("Trying to free not loaded sound");
            // TODO: throw a warning
            return;
        }

        ma_sound* raw = get_raw_sound();
        ma_sound_uninit(raw);
        loaded_sound = nullptr;
    }

    ma_sound* Sound::get_raw_sound() const {
        return loaded_sound.get();
    }
}