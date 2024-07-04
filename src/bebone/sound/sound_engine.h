#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <miniaudio.h>
#include <string>
#include <memory>
#include "sound.h"

namespace bebone::sound_system {
    class SoundEngine {
    private:
        ma_engine engine;

    public:
        SoundEngine();
        ~SoundEngine();

        Sound load_sound(const std::string& path);
    };
}

#endif
