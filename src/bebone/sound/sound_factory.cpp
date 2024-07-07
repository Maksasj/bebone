#include "sound_factory.h"

namespace bebone::sound_system {
    std::shared_ptr<ma_sound> LightweightSoundFactory::create_sound(ma_engine &engine, const std::string &path) {
        auto sound = std::make_shared<ma_sound>();

        ma_result result = ma_sound_init_from_file(&engine, path.c_str(), 0, NULL, NULL, sound.get());
        if (result != MA_SUCCESS) {
            // TODO: Throw an exception
        }

        return sound;
    }

    std::shared_ptr<ma_sound> StreamSoundFactory::create_sound(ma_engine &engine, const std::string &path) {
        auto sound = std::make_shared<ma_sound>();

        ma_result result = ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, sound.get());
        if (result != MA_SUCCESS) {
            // TODO: Throw an exception
        }

        return sound;
    }
}