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

        std::shared_ptr<ma_sound> init_sound(const std::string& path);
    public:
        SoundEngine();
        ~SoundEngine();

        std::shared_ptr<Sound> load_sound(const std::string& path);
        void load_sound(const std::string& path, const std::shared_ptr<Sound>& sound);
    };
}

#endif
