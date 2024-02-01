#ifndef _BEBONE_ASSETS_IMAGE_TPP_
#define _BEBONE_ASSETS_IMAGE_TPP_

#include <vector>
#include <memory>

#include <iostream>

#include "../../core/types.h"
#include "../../core/noncopyable.h"

#include <stb_image.h>
#include <stb_image_write.h>

namespace bebone::assets {
    using namespace bebone::core;

    template<typename _Color>
    class Image : public NonCopyable {
        private:
            std::vector<_Color> color;

            int width;
            int height;

        public:
            Image(const std::vector<_Color>& data, const size_t& width, const size_t& height) : color(data), width(width), height(height) {

            }

            Image(const size_t& width, const size_t& height, const _Color& color = _Color::WHITE) : color(width * height, color), width(width), height(height) {

            }

            _Color* data() {
                return color.data();
            }

            inline _Color& at(const size_t& offset) {
                return color[offset];
            }

            inline _Color& at(const size_t& x, const size_t& y) {
                return at(x + y * width);
            }

            const int& get_width() const {
                return width;
            }

            const int& get_height() const {
                return height;
            }

            size_t get_channels() const {
                return _Color::get_channels();
            }

            template<typename _DesiredColor>
            std::shared_ptr<Image<_DesiredColor>> to() const {
                std::vector<_DesiredColor> newColor(width * height);

                const auto size = width * height;

                for(auto i = 0; i < size; ++i)
                    newColor[i] = color[i].template to<_DesiredColor>();

                return std::make_shared<Image<_DesiredColor>>(newColor, width, height);
            }

            std::shared_ptr<Image<_Color>> clone() const {
                return std::make_shared<Image<_Color>>(color, width, height);
            }

            static std::shared_ptr<Image<_Color>> load_from_file(const std::string& filePath) {
                stbi_set_flip_vertically_on_load(true);

                int width, height, channels;
                void* bytes = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

                const auto size = width * height;

                if(channels == 3) {
                    auto* b = static_cast<ColorRGB24*>(bytes);

                    std::vector<_Color> color(size);

                    for(auto i = 0; i < size; ++i)
                        color[i] = b[i].to<_Color>();

                    stbi_image_free(bytes);

                    return std::make_shared<Image>(color, width, height);
                } else if(channels == 4) {
                    auto* b = static_cast<ColorRGBA32*>(bytes);

                    std::vector<_Color> color(size);

                    for(auto i = 0; i < size; ++i)
                        color[i] = b[i].to<_Color>();

                    stbi_image_free(bytes);

                    return std::make_shared<Image>(color, width, height);
                }

                throw std::runtime_error("Unsupported color format " + filePath);
            }

            void export_to_file(const std::string& fileName) {
                if(_Color::get_format() & OMNI_TYPES_COLOR_FLOAT) {
                    auto image = to<ColorRGBA32>();
                    const auto channels = image->get_channels();

                    stbi_write_png(fileName.c_str(), width, height, channels, image->data(), width*channels);
                } else {
                    const auto channels = get_channels();

                    stbi_write_png(fileName.c_str(), width, height, channels, data(), width*channels);
                }
            }
    };
}

#endif