#include "image.h"

namespace bebone::assets {
    using namespace bebone::core;

    template<typename Color>
    Image<Color>::Image(const std::vector<Color>& data, const size_t& width, const size_t& height) : color(data), width(width), height(height) {

    }

    template<typename Color>
    Color* Image<Color>::data() {
        return color.data();
    }

    template<typename Color>
    std::vector<Color>& Image<Color>::get_data() {
        return color;
    }

    template<typename Color>
    Color& Image<Color>::at(const size_t& offset) {
        return color[offset];
    }

    template<typename Color>
    Color& Image<Color>::at(const size_t& x, const size_t& y) {
        return at(x + y * width);
    }

    template<typename Color>
    Color& Image<Color>::at(const Vec2i& pos) {
        return at(pos.x, pos.y);
    }

    template<typename Color>
    const int& Image<Color>::get_width() const {
        return width;
    }

    template<typename Color>
    const int& Image<Color>::get_height() const {
        return height;
    }

    template<typename Color>
    size_t Image<Color>::get_channels() const {
        return Color::get_channels();
    }

    template<typename Color>
    size_t Image<Color>::get_size() const {
        return sizeof(Color) * color.size();
    }

    template<typename Color>
    template<typename DesiredColor>
    std::shared_ptr<Image<DesiredColor>> Image<Color>::to() const {
        std::vector<DesiredColor> newColor(width * height);

        const auto size = width * height;

        for(auto i = 0; i < size; ++i)
            newColor[i] = color[i].template to<DesiredColor>();

        return std::make_shared<Image<DesiredColor>>(newColor, width, height);
    }

    template<typename Color>
    std::shared_ptr<Image<Color>> Image<Color>::clone() const {
        return std::make_shared<Image<Color>>(color, width, height);
    }

    template<typename Color>
    std::shared_ptr<Image<Color>> Image<Color>::from_color(const size_t& width, const size_t& height, const Color& color) {
        return std::make_shared<Image<Color>>(std::vector<Color>(width * height, color), width, height);
    }

    template<typename Color>
    std::shared_ptr<Image<Color>> Image<Color>::from_white_noise(const size_t& width, const size_t & height) {
        const auto size = width * height;

        std::vector<Color> color(size);
        for(size_t i = 0; i < size; ++i)
            color[i] = ColorRGB24::monochrome(rand() % 255).to<Color>();

        return std::make_shared<Image<Color>>(color, width, height);
    }

    template<typename Color>
    std::shared_ptr<Image<Color>> Image<Color>::load_from_file(const std::string& file_path, const bool& v_flip) {
        stbi_set_flip_vertically_on_load(v_flip);

        int width, height, channels;
        void* bytes = stbi_load(file_path.c_str(), &width, &height, &channels, 0);

        const auto size = width * height;

        if(channels == 3) {
            auto* b = static_cast<ColorRGB24*>(bytes);

            std::vector<Color> color(size);

            for(auto i = 0; i < size; ++i)
                color[i] = b[i].to<Color>();

            stbi_image_free(bytes);

            return std::make_shared<Image>(color, width, height);
        } else if(channels == 4) {
            auto* b = static_cast<ColorRGBA32*>(bytes);

            std::vector<Color> color(size);

            for(auto i = 0; i < size; ++i)
                color[i] = b[i].to<Color>();

            stbi_image_free(bytes);

            return std::make_shared<Image>(color, width, height);
        }

        throw std::runtime_error("Unsupported color format " + file_path);
    }

    template<typename Color>
    void Image<Color>::export_to_file(const std::string& file_name) {
        if(Color::get_format() & BEBONE_TYPES_COLOR_FLOAT) {
            auto image = to<ColorRGBA32>();
            const auto channels = image->get_channels();

            stbi_write_png(file_name.c_str(), width, height, channels, image->data(), width*channels);
        } else {
            const auto channels = get_channels();

            stbi_write_png(file_name.c_str(), width, height, channels, data(), width*channels);
        }
    }

    template class Image<ColorRGB24>;
    template class Image<ColorRGBA32>;
    template class Image<ColorRGBA32F>;
}
