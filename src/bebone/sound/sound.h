#ifndef _SOUND_H_
#define _SOUND_H_

#include <miniaudio.h>
#include <memory>

namespace bebone::sound_system {
    class SoundEngine;

    class Sound {
    private:
        std::shared_ptr<ma_sound> loaded_sound;

        void free();
        ma_sound* get_raw_sound() const;
    public:
        Sound();
        ~Sound();

        void play() const;
        void stop() const;
        void rewind() const;

        void set_volume(const float& volume) const;
        void set_pan(const float& pan) const;
        void set_pitch(const float& pitch) const;
        void set_looping(const bool& loop) const;

        bool is_playing() const;
        bool at_end() const;
        bool is_looping() const;

        friend class SoundEngine;
    };
}

#endif
