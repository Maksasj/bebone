#ifndef _BEBONE_ASSETS_IMAGE_PAINTER_TPP_
#define _BEBONE_ASSETS_IMAGE_PAINTER_TPP_

#include <algorithm>

#include "../../core/types.h"
#include "../../core/noncopyable.h"

#include "image.h"

namespace bebone::assets {
    using namespace bebone::core;

    // Image painter class, class used for modification of an image
    template<typename _Color>
    class ImagePainter {
        private:
            std::shared_ptr<Image<_Color>> targetImage;

            // Hidden constructor
            explicit ImagePainter(const std::shared_ptr<Image<_Color>>& targetImage);
        public:
            // Todo, add Vec2i variants for this functions

            /*!
            * Sets image pixel color
            * @param xPos - Pixel X position
            * @param yPos - Pixel Y position
            * @param color - Color to be set
            */
            void paint_pixel(const size_t& xPos, const size_t& yPos, const _Color& color);

            /*!
            * Draws circle to the image
            * @param xPos - Circle center X position
            * @param yPos - Circle center Y position
            * @param radius - Circle radius
            * @param color - Circle color
            */
            void paint_circle(const size_t& xPos, const size_t& yPos, const f32& radius, const _Color& color);

            /*!
            * Draws square to the image
            * @param xPos - Square bottom left corner X position
            * @param yPos - Square bottom left corner Y position
            * @param sqWidth - Square width
            * @param sqHeight - Square height
            * @param color - Square color
            */
            void paint_square(const size_t& xPos, const size_t& yPos, const f32& sqWidth, const f32& sqHeight, const _Color& color);

            // Flips image vertically
            void flip_vertical();

            // Flips image horizontally
            void flip_horizontal();

            /*!
            * Resizes image
            * @param width - New image width
            * @param height - New image height
            */
            void resize(const size_t& width, const size_t& height);

            /*!
            * Crops specific image area
            * @param startX - Bottom left corner X position
            * @param startY - Bottom left corner Y position
            * @param width - Area width
            * @param height - Area height
            */
            void crop(const size_t& startX, const size_t& startY, const size_t& width, const size_t& height);

            /*!
            * Creates image painter object from an image
            * @param targetImage - Image that needs to be modified
            * @return ImagePainter class instance
            */
            static ImagePainter<_Color> from_image(const std::shared_ptr<Image<_Color>>& targetImage);
    };
}

#endif
