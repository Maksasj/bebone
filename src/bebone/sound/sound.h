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

        friend class SoundEngine;
    };
}

#endif
