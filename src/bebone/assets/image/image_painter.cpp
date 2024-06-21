#include "image_painter.h"

namespace bebone::assets {
    using namespace bebone::core;

    template<typename Color>
    ImagePainter<Color>::ImagePainter(const std::shared_ptr<Image<Color>>& target_image) : target_image(target_image) {

    }

    template<typename Color>
    void ImagePainter<Color>::paint_pixel(const size_t& x_pos, const size_t& y_pos, const Color& color) {
        const size_t height = target_image->get_height();
        target_image->at(x_pos, height - y_pos) = color;
    }

    template<typename Color>
    void ImagePainter<Color>::paint_circle(const size_t& x_pos, const size_t& y_pos, const f32& radius, const Color& color) {
        const auto r2 = radius * radius;

        const size_t width = target_image->get_width();
        const size_t height = target_image->get_height();

        for(f32 x = -radius; x < radius; ++x) {
        const f32 x2 = x*x;

        for(f32 y = -radius; y < radius; ++y) {
            if(x2 + y*y > r2) continue;

            const size_t x_cord = std::clamp((size_t) (x_pos + x), (size_t) 0, width - 1);
            const size_t y_cord = std::clamp((size_t) (y_pos + y), (size_t) 0, height - 1);

            target_image->at(x_cord, height - y_cord) = color;
            }
        }
    }

    template<typename Color>
    void ImagePainter<Color>::paint_square(const size_t& x_pos, const size_t& y_pos, const f32& sq_width, const f32& sq_height, const Color& color) {
        const size_t width = target_image->get_width();
        const size_t height = target_image->get_height();

        for(auto x = -sq_width; x < sq_width; ++x) {
            for(auto y = -sq_height; y < sq_height; ++y) {
                const size_t x_cord = std::clamp((size_t) (static_cast<f32>(x_pos) + static_cast<f32>(x)), (size_t) 0, width - 1);
                const size_t y_cord = std::clamp((size_t) (static_cast<f32>(y_pos) + static_cast<f32>(y)), (size_t) 0, height - 1);

                target_image->at(x_cord, height - y_cord) = color;
            }
        }
    }

    template<typename Color>
    void ImagePainter<Color>::flip_vertical() {
        const size_t width = target_image->get_width() - 1;
        const size_t height = target_image->get_height() - 1;

        const size_t h_width = width / 2;

        for(size_t x = 0; x <= h_width; ++x) {
            for (size_t y = 0; y <= height; ++y) {
                auto& pl = target_image->at(x, y);
                auto& pr = target_image->at(width - x, y);

                std::swap(pl, pr);
            }
        }
    }

    template<typename Color>
    void ImagePainter<Color>::flip_horizontal() {
        const size_t width = target_image->get_width() - 1;
        const size_t height = target_image->get_height() - 1;

        const size_t h_height = height / 2;

        for(size_t x = 0; x <= width; ++x) {
            for (size_t y = 0; y <= h_height; ++y) {
                auto& pl = target_image->at(x, y);
                auto& pr = target_image->at(x, height - y);

                std::swap(pl, pr);
            }
        }
    }

    template<typename Color>
    void ImagePainter<Color>::resize(const size_t& width, const size_t& height) {
        std::vector<Color> color(width * height);

        const size_t start_w = target_image->get_width() - 1;
        const size_t start_h = target_image->get_height() - 1;

        auto index = 0;

        for(size_t x = 0; x < width; ++x) {
            for (size_t y = 0; y < height; ++y) {
                const auto uv_x = static_cast<f32>(x) / static_cast<f32>(width);
                const auto uv_y = static_cast<f32>(y) / static_cast<f32>(height);

                const size_t pixel_x = round(uv_x * start_w);
                const size_t pixel_y = round(uv_y * start_h);

                color[index] = target_image->at(pixel_x, pixel_y);
                ++index;
            }
        }

        target_image->color = color;
        target_image->width = width;
        target_image->height = height;
    }

    template<typename Color>
    void ImagePainter<Color>::crop(const size_t& start_x, const size_t& start_y, const size_t& width, const size_t& height) {
        const auto end_x = start_x + width;
        const auto end_y = start_y + height;

        std::vector<Color> color(width * height);

        auto index = 0;

        for(size_t x = start_x; x < end_x; ++x) {
            for (size_t y = start_y; y < end_y; ++y) {
                color[index] = target_image->at(x, y);
                ++index;
            }
        }

        target_image->color = color;
        target_image->width = width;
        target_image->height = height;
    }

    template<typename Color>
    ImagePainter<Color> ImagePainter<Color>::from_image(const std::shared_ptr<Image<Color>>& target_image) {
        return ImagePainter<Color>(target_image);
    }

    template class ImagePainter<ColorRGB24>;
    template class ImagePainter<ColorRGBA32>;
    template class ImagePainter<ColorRGBA32F>;
}

