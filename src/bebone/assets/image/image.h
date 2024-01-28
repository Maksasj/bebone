#ifndef _BEBONE_ASSETS_IMAGE_H_
#define _BEBONE_ASSETS_IMAGE_H_

#include <vector>
#include <memory>

#include <iostream>

#include "../../core/types.h"
#include "../../core/noncopyable.h"

#include <stb_image.h>

namespace bebone::assets {
    using namespace bebone::core;

    class Image : public NonCopyable {
        private:
            std::vector<u8> color;

            int width;
            int height;
            int channels;

        public:
            Image(void* data, const size_t& width, const size_t& height, const size_t& channels) : width(width), height(height), channels(channels) {
                color.reserve(width * height * channels);

                memcpy(color.data(), data, width * height * channels);

                stbi_image_free(data);
            }

            static std::shared_ptr<Image> load_from_file(const std::string& filePath) {
                int width, height, channels;

                auto* bytes = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

                return std::make_shared<Image>(bytes, width, height, channels);
            }

            void* data() {
                return color.data();
            }

            const int& get_width() const {
                return width;
            }

            const int& get_height() const {
                return height;
            }

            const int& get_channels() const {
                return channels;
            }
    };
}

#endif