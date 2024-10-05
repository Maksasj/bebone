#include "sound_engine.h"

namespace bebone::sound_system {
    SoundEngine::SoundEngine() {
        ma_result result = ma_engine_init(NULL, &engine);

        if (result != MA_SUCCESS) {
            LOG_ERROR("Failed to initialize sound engine");
            // TODO: Throw an exception
        }
    }

    SoundEngine::~SoundEngine() {
        ma_engine_uninit(&engine);
    }

    std::shared_ptr<Sound> SoundEngine::load_sound(const std::string& path, const std::shared_ptr<SoundFactory>& sound_factory) {
        std::shared_ptr<Sound> sound = std::make_shared<Sound>();
        sound->loaded_sound = sound_factory->create_sound(engine, path);

        return sound;
    }

    void SoundEngine::load_sound(const std::string& path, const std::shared_ptr<Sound>& sound, const std::shared_ptr<SoundFactory>& sound_factory) {
        sound->free();
        sound->loaded_sound = sound_factory->create_sound(engine, path);
    }
}