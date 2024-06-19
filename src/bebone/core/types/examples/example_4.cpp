#include <iostream>

#include "omni_types.tpp"

int main() {
    using namespace omni::types;

    Mat4f a = trait_bryan_angle_yxz(Vec3f::splat(0.0f));

    std::cout << a.to_string() << "\n";

    return 0;
}