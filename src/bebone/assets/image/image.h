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
            Image(const std::vector<_Color>& data, const size_t& width, const size_t& height);

            _Color* data();

            _Color& at(const size_t& offset);
            _Color& at(const size_t& x, const size_t& y);

            const int& get_width() const;
            const int& get_height() const;
            size_t get_channels() const;

            size_t get_size() const;

            template<typename _DesiredColor>
            std::shared_ptr<Image<_DesiredColor>> to() const;

            std::shared_ptr<Image<_Color>> clone() const;

            static std::shared_ptr<Image<_Color>> from_color(const size_t& width, const size_t& height, const _Color& color = _Color::WHITE);
            static std::shared_ptr<Image<_Color>> from_white_noise(const size_t& width, const size_t & height);

            static std::shared_ptr<Image<_Color>> load_from_file(const std::string& filePath);

            void export_to_file(const std::string& fileName);
    };
}

#endif