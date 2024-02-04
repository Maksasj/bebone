#ifndef _BEBONE_ASSETS_IMAGE_PAINTER_TPP_
#define _BEBONE_ASSETS_IMAGE_PAINTER_TPP_

#include <algorithm>

#include "../../core/types.h"
#include "../../core/noncopyable.h"

#include "image.h"

namespace bebone::assets {
    using namespace bebone::core;

    template<typename _Color>
    class ImagePainter {
         private:
             std::shared_ptr<Image<_Color>> targetImage;

             explicit ImagePainter(const std::shared_ptr<Image<_Color>>& targetImage);
        public:
             void paint_pixel(const size_t& xPos, const size_t& yPos, const _Color& color);

             void paint_circle(const size_t& xPos, const size_t& yPos, const f32& radius, const _Color& color);
             void paint_square(const size_t& xPos, const size_t& yPos, const f32& sqWidth, const f32& sqHeight, const _Color& color);

             static ImagePainter<_Color> from_image(const std::shared_ptr<Image<_Color>>& targetImage);
    };
}

#endif