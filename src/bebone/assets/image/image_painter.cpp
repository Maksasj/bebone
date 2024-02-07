#include "image_painter.h"

namespace bebone::assets {
    using namespace bebone::core;

    template<typename _Color>
    ImagePainter<_Color>::ImagePainter(const std::shared_ptr<Image<_Color>>& targetImage) : targetImage(targetImage) {

    }

    template<typename _Color>
    void ImagePainter<_Color>::paint_pixel(const size_t& xPos, const size_t& yPos, const _Color& color) {
        const size_t height = targetImage->get_height();
        targetImage->at(xPos, height - yPos) = color;
    }

    template<typename _Color>
    void ImagePainter<_Color>::paint_circle(const size_t& xPos, const size_t& yPos, const f32& radius, const _Color& color) {
        const auto r2 = radius * radius;

        const size_t width = targetImage->get_width();
        const size_t height = targetImage->get_height();

        for(f32 x = -radius; x < radius; ++x) {
        const f32 x2 = x*x;

        for(f32 y = -radius; y < radius; ++y) {
            if(x2 + y*y > r2) continue;

            const size_t xCord = std::clamp((size_t) (xPos + x), (size_t) 0, width - 1);
            const size_t yCord = std::clamp((size_t) (yPos + y), (size_t) 0, height - 1);

            targetImage->at(xCord, height - yCord) = color;
            }
        }
    }

    template<typename _Color>
    void ImagePainter<_Color>::paint_square(const size_t& xPos, const size_t& yPos, const f32& sqWidth, const f32& sqHeight, const _Color& color) {
        const size_t width = targetImage->get_width();
        const size_t height = targetImage->get_height();

        for(auto x = -sqWidth; x < sqWidth; ++x) {
            for(auto y = -sqHeight; y < sqHeight; ++y) {
                const size_t xCord = std::clamp((size_t) (static_cast<f32>(xPos) + static_cast<f32>(x)), (size_t) 0, width - 1);
                const size_t yCord = std::clamp((size_t) (static_cast<f32>(yPos) + static_cast<f32>(y)), (size_t) 0, height - 1);

                targetImage->at(xCord, height - yCord) = color;
            }
        }
    }

    template<typename _Color>
    void ImagePainter<_Color>::flip_vertical() {
        const size_t width = targetImage->get_width() - 1;
        const size_t height = targetImage->get_height() - 1;

        const size_t hWidth = width / 2;

        for(size_t x = 0; x <= hWidth; ++x) {
            for (size_t y = 0; y <= height; ++y) {
                auto& pl = targetImage->at(x, y);
                auto& pr = targetImage->at(width - x, y);

                std::swap(pl, pr);
            }
        }
    }

    template<typename _Color>
    void ImagePainter<_Color>::flip_horizontal() {
        const size_t width = targetImage->get_width() - 1;
        const size_t height = targetImage->get_height() - 1;

        const size_t hHeight = height / 2;

        for(size_t x = 0; x <= width; ++x) {
            for (size_t y = 0; y <= hHeight; ++y) {
                auto& pl = targetImage->at(x, y);
                auto& pr = targetImage->at(x, height - y);

                std::swap(pl, pr);
            }
        }
    }

    template<typename _Color>
    void ImagePainter<_Color>::resize(const size_t& width, const size_t& height) {
        std::vector<_Color> color(width * height);

        const size_t startW = targetImage->get_width() - 1;
        const size_t startH = targetImage->get_height() - 1;

        auto index = 0;

        for(size_t x = 0; x < width; ++x) {
            for (size_t y = 0; y < height; ++y) {
                const auto uvX = static_cast<f32>(x) / static_cast<f32>(width);
                const auto uvY = static_cast<f32>(y) / static_cast<f32>(height);

                const size_t pixelX = round(uvX * startW);
                const size_t pixelY = round(uvY * startH);

                color[index] = targetImage->at(pixelX, pixelY);
                ++index;
            }
        }

        targetImage->color = color;
        targetImage->width = width;
        targetImage->height = height;
    }

    template<typename _Color>
    void ImagePainter<_Color>::crop(const size_t& startX, const size_t& startY, const size_t& width, const size_t& height) {
        const auto endX = startX + width;
        const auto endY = startY + height;

        std::vector<_Color> color(width * height);

        auto index = 0;

        for(size_t x = startX; x < endX; ++x) {
            for (size_t y = startY; y < endY; ++y) {
                color[index] = targetImage->at(x, y);
                ++index;
            }
        }

        targetImage->color = color;
        targetImage->width = width;
        targetImage->height = height;
    }

    template<typename _Color>
    ImagePainter<_Color> ImagePainter<_Color>::from_image(const std::shared_ptr<Image<_Color>>& targetImage) {
        return ImagePainter<_Color>(targetImage);
    }

    template class ImagePainter<ColorRGB24>;
    template class ImagePainter<ColorRGBA32>;
    template class ImagePainter<ColorRGBA32f>;
}

