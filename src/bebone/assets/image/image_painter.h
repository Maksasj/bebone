#ifndef _BEBONE_ASSETS_IMAGE_PAINTER_TPP_
#define _BEBONE_ASSETS_IMAGE_PAINTER_TPP_

#include <algorithm>

#include "../../core/core.h"

#include "image.h"

namespace bebone::assets {
    using namespace bebone::core;

    // Image painter class, class used for modification of an image
    template<typename Color>
    class ImagePainter {
        private:
            std::shared_ptr<Image<Color>> target_image;

            // Hidden constructor
            explicit ImagePainter(const std::shared_ptr<Image<Color>>& target_image);
        public:
            /*!
            * Sets image pixel color
            * @param x_pos - Pixel X position
            * @param y_pos - Pixel Y position
            * @param color - Color to be set
            */
            void paint_pixel(const size_t& x_pos, const size_t& y_pos, const Color& color);

            /*!
            * Sets image pixel color
            * @param pos - Pixel position
            * @param color - Color to be set
            */
            void paint_pixel(const Vec2i& pos, const Color& color);

            /*!
            * Draws circle to the image
            * @param x_pos - Circle center X position
            * @param y_pos - Circle center Y position
            * @param radius - Circle radius
            * @param color - Circle color
            */
            void paint_circle(const size_t& x_pos, const size_t& y_pos, const f32& radius, const Color& color);

            /*!
            * Draws circle to the image
            * @param pos - Circle center position
            * @param radius - Circle radius
            * @param color - Circle color
            */
            void paint_circle(const Vec2i& pos, const f32& radius, const Color& color);

            /*!
            * Draws square to the image
            * @param x_pos - Square bottom left corner X position
            * @param y_pos - Square bottom left corner Y position
            * @param sq_width - Square width
            * @param sq_height - Square height
            * @param color - Square color
            */
            void paint_square(const size_t& x_pos, const size_t& y_pos, const f32& sq_width, const f32& sq_height, const Color& color);

            /*!
            * Draws square to the image
            * @param pos - Square bottom left corner position
            * @param size - Square size
            * @param color - Square color
            */
            void paint_square(const Vec2i& pos, const Vec2i& size, const Color& color);

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
            * Resizes image
            * @param size - New image size
            */
            void resize(const Vec2i& size);

            /*!
            * Crops specific image area
            * @param start_x - Bottom left corner X position
            * @param start_y - Bottom left corner Y position
            * @param width - Area width
            * @param height - Area height
            */
            void crop(const size_t& start_x, const size_t& start_y, const size_t& width, const size_t& height);

            /*!
            * Crops specific image area
            * @param pos - Bottom left corner position
            * @param size - Area size
            */
            void crop(const Vec2i& pos, const Vec2i& size);

            /*!
            * Creates image painter object from an image
            * @param target_image - Image that needs to be modified
            * @return ImagePainter class instance
            */
            static ImagePainter<Color> from_image(const std::shared_ptr<Image<Color>>& target_image);
    };
}

#endif
