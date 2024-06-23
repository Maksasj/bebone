#include "color_r8g8b8.tpp"

#include "color_r8g8b8a8.tpp"
#include "color_rgba32f.tpp"

namespace bebone::core {
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::BLACK{0, 0, 0};
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::WHITE{255, 255, 255};
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::RED{255, 0, 0};
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::BLUE{0, 0, 255};
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::GREEN{0, 255, 0};
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::YELLOW{255, 255, 0};
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::MAGENTA{255, 0, 255};
    const Color<R8G8B8Uint> Color<R8G8B8Uint>::CYAN{0, 255, 255};

    template<>
    Color<R8G8B8Uint> Color<R8G8B8Uint>::to() const {
        return *this;
    }

    template<>
    Color<R8G8B8A8Uint> Color<R8G8B8Uint>::to() const {
        return Color<R8G8B8A8Uint>{r, g, b, 255};
    }

    template<>
    Color<R32G32B32A32Float> Color<R8G8B8Uint>::to() const {
        return Color<R32G32B32A32Float>{
            static_cast<f32>(r) / 255.0f,
            static_cast<f32>(g) / 255.0f,
            static_cast<f32>(b) / 255.0f,
            1.0f
        };
    }
}
