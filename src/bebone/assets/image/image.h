#ifndef _BEBONE_ASSETS_IMAGE_TPP_
#define _BEBONE_ASSETS_IMAGE_TPP_

#include <vector>
#include <memory>

#include <iostream>

#include "../../core/types.h"
#include "../../core/noncopyable.h"

#include <stb_image.h>
#include <stb_image_write.h>

namespace bebone::assets {
    using namespace bebone::core;

    // Pixel data wrapper class
    template<typename Color>
    class Image : public NonCopyable {
        private:
            std::vector<Color> color;

            int width;
            int height;

        public:
            template<typename ImagePainterColor>
            friend class ImagePainter;

            /*!
            * Default constructor
            * @param data - Pixel data
            * @param width - Image width
            * @param height - Image height
            */
            Image(const std::vector<Color>& data, const size_t& width, const size_t& height);

            /*!
            * Get a pointer to image pixel data
            * @return Pointer to pixel data
            */
            Color* data();

            // Reference pixel data container
            std::vector<Color>& get_data();

            /*!
            * Get a pixel from some linear offset
            * @param offset - Pixel offset
            * @return Pixel reference
            */
            Color& at(const size_t& offset);

            /*!
            * Get a pixel at some position
            * @param x - Pixel x position
            * @param y - Pixel y position
            * @return Pixel reference
            */
            Color& at(const size_t& x, const size_t& y);

            /*!
            * Get a pixel at some position
            * @param pos - Pixel position
            * @return Pixel reference
            */
            Color& at(const Vec2i& pos);

            // Image width getter
            const int& get_width() const;

            // Image height getter
            const int& get_height() const;

            // Image channel count getter
            size_t get_channels() const;

            /*!
             * Get a byte size of the image data
             * @return Size
            */
            size_t get_size() const;

            /*!
            * Convert image to desired color format
            * @return New image
            */
            template<typename DesiredColor>
            std::shared_ptr<Image<DesiredColor>> to() const;

            /*!
            * Clone image, also cloning image pixel data
            * @return New image
            */
            std::shared_ptr<Image<Color>> clone() const;

            /*!
            * Generate image of plain color
            * @param width - Desired image width
            * @param height - Desired image height
            * @param color - Desired image color
            * @return New image
            */
            static std::shared_ptr<Image<Color>> from_color(const size_t& width, const size_t& height, const Color& color = Color::WHITE);

            /*!
            * Generate white noise image
            * @param width - Desired image width
            * @param height - Desired image height
            * @return New image
            */
            static std::shared_ptr<Image<Color>> from_white_noise(const size_t& width, const size_t & height);

            /*!
            * Load image from file
            * @param file_path - File path to the image file
            * @param v_flip - Verticall flip flag
            * @return Image
            */
            static std::shared_ptr<Image<Color>> load_from_file(const std::string& file_path, const bool& v_flip = true);

            /*!
            * Export image to file
            * @param file_name - file name
            */
            void export_to_file(const std::string& file_name);
    };
}

#endif