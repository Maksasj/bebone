#include "sound_engine.h"

namespace bebone::sound_system {
    SoundEngine::SoundEngine() {
        ma_result result = ma_engine_init(NULL, &engine);

        if (result != MA_SUCCESS) {
            // TODO: Throw an exception
        }
    }

    SoundEngine::~SoundEngine() {
        ma_engine_uninit(&engine);
    }

    std::shared_ptr<Sound> SoundEngine::load_sound(const std::string& path) {
        std::shared_ptr<Sound> sound = std::make_shared<Sound>();
        sound->loaded_sound = init_sound(path);

        return sound;
    }

    void SoundEngine::load_sound(const std::string& path, const std::shared_ptr<Sound>& sound) {
        sound->free();
        sound->loaded_sound = init_sound(path);
    }

    std::shared_ptr<ma_sound> SoundEngine::init_sound(const std::string& path) {
        auto sound = std::make_shared<ma_sound>();

        ma_result result = ma_sound_init_from_file(&engine, path.c_str(), 0, NULL, NULL, sound.get());
        if (result != MA_SUCCESS) {
            // TODO: Throw an exception
        }

        return sound;
    }
}