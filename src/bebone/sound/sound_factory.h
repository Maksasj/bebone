#ifndef _SOUND_FACTORY_H_
#define _SOUND_FACTORY_H_

#include <memory>
#include <string>
#include "sound.h"
#include <miniaudio.h>

namespace bebone::sound_system {
    class SoundFactory {
    public:
        virtual std::shared_ptr<ma_sound> create_sound(ma_engine& engine, const std::string& path) = 0;
    };

    class LightweightSoundFactory : public SoundFactory {
    public:
        std::shared_ptr<ma_sound> create_sound(ma_engine& engine, const std::string& path) override;
    };

    class StreamSoundFactory : public SoundFactory {
    public:
        std::shared_ptr<ma_sound> create_sound(ma_engine& engine, const std::string& path) override;
    };
}

#endif
