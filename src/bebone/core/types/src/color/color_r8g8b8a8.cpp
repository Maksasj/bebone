#include "color_r8g8b8a8.tpp"

#include "color_r8g8b8.tpp"
#include "color_rgba32f.tpp"

namespace omni::types {
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::BLACK{0, 0, 0, 255};
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::WHITE{255, 255, 255, 255};
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::RED{255, 0, 0, 255};
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::BLUE{0, 0, 255, 255};
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::GREEN{0, 255, 0, 255};
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::YELLOW{255, 255, 0, 255};
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::MAGENTA{255, 0, 255, 255};
    const Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::CYAN{0, 255, 255, 255};

    template<>
    Color<R8G8B8_UINT> Color<R8G8B8A8_UINT>::to() const {
        return Color<R8G8B8_UINT>{r, g, b};
    }

    template<>
    Color<R8G8B8A8_UINT> Color<R8G8B8A8_UINT>::to() const {
        return *this;
    }

    template<>
    Color<R32G32B32A32_FLOAT> Color<R8G8B8A8_UINT>::to() const {
        return Color<R32G32B32A32_FLOAT>{
            static_cast<f32>(r) / 255.0f,
            static_cast<f32>(g) / 255.0f,
            static_cast<f32>(b) / 255.0f,
            static_cast<f32>(a) / 255.0f
        };
    }
}
