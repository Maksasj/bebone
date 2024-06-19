#include "color_rgba32f.tpp"

#include "color_r8g8b8.tpp"
#include "color_r8g8b8a8.tpp"

namespace omni::types {
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::BLACK{0.0f, 0.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::WHITE{1.0f, 1.0f, 1.0f, 1.0f};
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::RED{1.0f, 0.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::BLUE{0.0f, 0.0f, 1.0f, 1.0f};
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::GREEN{0.0f, 1.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::YELLOW{1.0f, 1.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::MAGENTA{1.0f, 0.0f, 1.0f, 1.0f};
    const Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::CYAN{0.0f, 1.0f, 1.0f, 1.0f};

    template<>
    Color<R8G8B8_UINT> Color<R32G32B32A32_FLOAT>::to() const {
        return Color<R8G8B8_UINT>{
            static_cast<u8>(r * 255),
            static_cast<u8>(g * 255),
            static_cast<u8>(b * 255)
        };
    }

    template<>
    Color<R8G8B8A8_UINT> Color<R32G32B32A32_FLOAT>::to() const {
        return Color<R8G8B8A8_UINT>{
            static_cast<u8>(r * 255),
            static_cast<u8>(g * 255),
            static_cast<u8>(b * 255),
            static_cast<u8>(a * 255)
        };
    }

    template<>
    Color<R32G32B32A32_FLOAT> Color<R32G32B32A32_FLOAT>::to() const {
        return *this;
    }
}
