#include <iostream>

#include "omni_types.tpp"

int main() {
    using namespace omni::types;

    {
        Mat4f a = {{5, 2, 6, 1, 0, 6, 2, 0, 3, 8, 1, 4, 1, 8, 5, 6}};
        Mat4f b = {{7, 5, 8, 0, 1, 8, 2, 6, 9, 4, 3, 8, 5, 3, 7, 9}};

        std::cout << (a * b).to_string() << "\n";
    }

    {
        Mat4f a = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
        Mat4f b = {{17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}};


        std::cout << (a * b).to_string() << "\n";
    }

    return 0;
}