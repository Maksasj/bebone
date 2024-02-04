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
    ImagePainter<_Color> ImagePainter<_Color>::from_image(const std::shared_ptr<Image<_Color>>& targetImage) {
        return ImagePainter<_Color>(targetImage);
    }

    template class ImagePainter<ColorRGB24>;
    template class ImagePainter<ColorRGBA32>;
    template class ImagePainter<ColorRGBA32f>;
}

