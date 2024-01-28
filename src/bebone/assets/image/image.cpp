#include "image.h"

namespace bebone::assets {
    Image::Image(void* data, const size_t& width, const size_t& height, const size_t& channels) : width(width), height(height), channels(channels) {
        color.reserve(width * height * channels);

        memcpy(color.data(), data, width * height * channels);

        stbi_image_free(data);
    }

    void* Image::data() {
        return color.data();
    }

    const int& Image::get_width() const {
        return width;
    }

    const int& Image::get_height() const {
        return height;
    }

    const int& Image::get_channels() const {
        return channels;
    }

    std::shared_ptr<Image> Image::load_from_file(const std::string& filePath) {
        int width, height, channels;

        auto* bytes = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

        return std::make_shared<Image>(bytes, width, height, channels);
    }
}
