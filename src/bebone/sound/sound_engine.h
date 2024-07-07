#ifndef _SOUND_ENGINE_H_
#define _SOUND_ENGINE_H_

#include <miniaudio.h>
#include <string>
#include <memory>
#include "sound.h"
#include "sound_factory.h"

namespace bebone::sound_system {
    class SoundEngine {
    private:
        ma_engine engine;
    public:
        SoundEngine();
        ~SoundEngine();

        std::shared_ptr<Sound> load_sound(const std::string& path,
                        const std::shared_ptr<SoundFactory>& sound_factory = std::make_shared<LightweightSoundFactory>());

        void load_sound(const std::string& path, const std::shared_ptr<Sound>& sound,
                        const std::shared_ptr<SoundFactory>& sound_factory = std::make_shared<LightweightSoundFactory>());
    };
}

#endif
