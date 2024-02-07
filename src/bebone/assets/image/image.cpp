#include "image.h"

namespace bebone::assets {
    using namespace bebone::core;

    template<typename _Color>
    Image<_Color>::Image(const std::vector<_Color>& data, const size_t& width, const size_t& height) : color(data), width(width), height(height) {

    }

    template<typename _Color>
    _Color* Image<_Color>::data() {
        return color.data();
    }

    template<typename _Color>
    _Color& Image<_Color>::at(const size_t& offset) {
        return color[offset];
    }

    template<typename _Color>
    _Color& Image<_Color>::at(const size_t& x, const size_t& y) {
        return at(x + y * width);
    }

    template<typename _Color>
    const int& Image<_Color>::get_width() const {
        return width;
    }

    template<typename _Color>
    const int& Image<_Color>::get_height() const {
        return height;
    }

    template<typename _Color>
    size_t Image<_Color>::get_channels() const {
        return _Color::get_channels();
    }

    template<typename _Color>
    size_t Image<_Color>::get_size() const {
        return sizeof(_Color) * color.size();
    }

    template<typename _Color>
    template<typename _DesiredColor>
    std::shared_ptr<Image<_DesiredColor>> Image<_Color>::to() const {
        std::vector<_DesiredColor> newColor(width * height);

        const auto size = width * height;

        for(auto i = 0; i < size; ++i)
            newColor[i] = color[i].template to<_DesiredColor>();

        return std::make_shared<Image<_DesiredColor>>(newColor, width, height);
    }

    template<typename _Color>
    std::shared_ptr<Image<_Color>> Image<_Color>::clone() const {
        return std::make_shared<Image<_Color>>(color, width, height);
    }

    template<typename _Color>
    std::shared_ptr<Image<_Color>> Image<_Color>::from_color(const size_t& width, const size_t& height, const _Color& color) {
        return std::make_shared<Image<_Color>>(std::vector<_Color>(width * height, color), width, height);
    }

    template<typename _Color>
    std::shared_ptr<Image<_Color>> Image<_Color>::from_white_noise(const size_t& width, const size_t & height) {
        const auto size = width * height;

        std::vector<_Color> color(size);
        for(size_t i = 0; i < size; ++i)
            color[i] = ColorRGB24::monochrome(rand() % 255).to<_Color>();

        return std::make_shared<Image<_Color>>(color, width, height);
    }

    template<typename _Color>
    std::shared_ptr<Image<_Color>> Image<_Color>::load_from_file(const std::string& filePath) {
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

    template<typename _Color>
    void Image<_Color>::export_to_file(const std::string& fileName) {
        if(_Color::get_format() & OMNI_TYPES_COLOR_FLOAT) {
            auto image = to<ColorRGBA32>();
            const auto channels = image->get_channels();

            stbi_write_png(fileName.c_str(), width, height, channels, image->data(), width*channels);
        } else {
            const auto channels = get_channels();

            stbi_write_png(fileName.c_str(), width, height, channels, data(), width*channels);
        }
    }

    template class Image<ColorRGB24>;
    template class Image<ColorRGBA32>;
    template class Image<ColorRGBA32f>;
}
