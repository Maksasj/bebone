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
            Image(void *data, const size_t &width, const size_t &height, const size_t &channels);

            void *data();

            const int &get_width() const;
            const int &get_height() const;
            const int &get_channels() const;

            static std::shared_ptr<Image> load_from_file(const std::string &filePath);
    };
}

#endif