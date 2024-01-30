#ifndef _BEBONE_ASSETS_IMAGE_PAINTER_TPP_
#define _BEBONE_ASSETS_IMAGE_PAINTER_TPP_

#include <algorithm>

#include "../../core/types.h"
#include "../../core/noncopyable.h"

#include "image.tpp"

namespace bebone::assets {
    using namespace bebone::core;

    template<typename _Color>
    class ImagePainter {
         private:
             std::shared_ptr<Image<_Color>> targetImage;

             explicit ImagePainter(const std::shared_ptr<Image<_Color>>& targetImage) : targetImage(targetImage) {

             }
         public:
             inline void paint_pixel(const size_t& xPos, const size_t& yPos, const _Color& color) {
                 targetImage->at(xPos, yPos) = color;
             }

             inline void paint_circle(const size_t& xPos, const size_t& yPos, const f32& radius, const _Color& color) {
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

             inline void paint_square(const size_t& xPos, const size_t& yPos, const f32& sqWidth, const f32& sqHeight, const _Color& color) {
                 const size_t width = targetImage->get_width();
                 const size_t height = targetImage->get_height();

                 for(f32 x = -sqWidth; x < sqWidth; ++x) {
                     for(f32 y = -sqHeight; y < sqHeight; ++y) {
                         const size_t xCord = std::clamp((size_t) (xPos + x), (size_t) 0, width - 1);
                         const size_t yCord = std::clamp((size_t) (yPos + y), (size_t) 0, height - 1);

                         targetImage->at(xCord, height - yCord) = color;
                     }
                 }
             }

             static ImagePainter<_Color> from_image(const std::shared_ptr<Image<_Color>>& targetImage) {
                 return ImagePainter<_Color>(targetImage);
             }
    };
}

#endif