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
        ma_sound* get_raw_sound();
    public:
        Sound();
        ~Sound();

        void play();
        void stop();
        void rewind();

        void set_volume(const float& volume);
        void set_pan(const float& pan);
        void set_pitch(const float& pitch);
        void set_looping(const bool& loop);

        bool is_playing();
        bool at_end();
        bool is_looping();

        friend class SoundEngine;
    };
}

#endif
