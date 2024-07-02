#include "color_rgba32f.tpp"

#include "color_r8g8b8.tpp"
#include "color_r8g8b8a8.tpp"

namespace bebone::core {
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::BLACK{0.0f, 0.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::WHITE{1.0f, 1.0f, 1.0f, 1.0f};
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::RED{1.0f, 0.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::BLUE{0.0f, 0.0f, 1.0f, 1.0f};
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::GREEN{0.0f, 1.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::YELLOW{1.0f, 1.0f, 0.0f, 1.0f};
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::MAGENTA{1.0f, 0.0f, 1.0f, 1.0f};
    const Color<R32G32B32A32Float> Color<R32G32B32A32Float>::CYAN{0.0f, 1.0f, 1.0f, 1.0f};

    template<>
    Color<R8G8B8Uint> Color<R32G32B32A32Float>::to() const {
        return Color<R8G8B8Uint>{
            static_cast<u8>(r * 255),
            static_cast<u8>(g * 255),
            static_cast<u8>(b * 255)
        };
    }

    template<>
    Color<R8G8B8A8Uint> Color<R32G32B32A32Float>::to() const {
        return Color<R8G8B8A8Uint>{
            static_cast<u8>(r * 255),
            static_cast<u8>(g * 255),
            static_cast<u8>(b * 255),
            static_cast<u8>(a * 255)
        };
    }

    template<>
    Color<R32G32B32A32Float> Color<R32G32B32A32Float>::to() const {
        return *this;
    }
}
