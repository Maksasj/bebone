#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_H_

#include "../../assets/image/image.h"
#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    struct GLTextureParameters {
        vector<pair<GLenum, GLint>> parameters = {
            {GL_TEXTURE_MIN_FILTER, GL_NEAREST},
            {GL_TEXTURE_MAG_FILTER, GL_NEAREST},
            {GL_TEXTURE_WRAP_S, GL_NEAREST},
            {GL_TEXTURE_WRAP_T, GL_NEAREST},
        };
    };

    class GLTexture : private core::NonCopyable {
        private:
            GLuint id;
            GLenum textureType;

        protected:
            void configure_gl_texture(const GLTextureParameters& parameters);
            void generate_mipmap();

        public:
            /*!
            * Default GLTexture constructor
            * @param textureType - opengl texture type
            */
            GLTexture(const GLenum& textureType);
            ~GLTexture();

            // Getter for opengl texture handle
            const GLuint& get_id() const;

            // Getter for texture type
            const GLenum& get_texture_type() const;

            /*!
             * Binds texture to the specified texture unit
             * @param textureUnit - texture unit, to which texture should be bound to
             */
            void bind_texture_unit(const GLuint& textureUnit);

            /// Binds texture
            void bind();

            /// Unbinds texture
            void unbind();

            /// Destroys texture. Calls automatically in the destructor
            void destroy();
    };
}

#endif
