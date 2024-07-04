#include "sound_engine.h"

namespace bebone::sound_system {
    SoundEngine::SoundEngine() {
        ma_result result = ma_engine_init(NULL, &engine);

        if (result != MA_SUCCESS) {
            // Throw an exception
        }
    }

    SoundEngine::~SoundEngine() {
        ma_engine_uninit(&engine);
    }

    Sound SoundEngine::load_sound(const std::string &path) {
        Sound sound;
        ma_sound raw_sound;

        ma_result result = ma_sound_init_from_file(&engine, path.c_str(), 0, NULL, NULL, &raw_sound);
        if (result != MA_SUCCESS) {
            // Throw an exception
        }

        sound.loaded_sound = &raw_sound;
        return sound;
    }
}