#ifndef _SOUND_H_
#define _SOUND_H_

#include <miniaudio.h>

namespace bebone::sound_system {
    class SoundEngine;

    class Sound {
    private:
        ma_sound* loaded_sound;

    public:
        Sound();
        ~Sound();

        void play();

        friend class SoundEngine;
    };
}

#endif
