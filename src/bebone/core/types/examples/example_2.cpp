#include <iostream>

#include "omni_types.tpp"

int main() {
    using namespace omni::types;

    UUID uuid = UUID::gen();

    std::cout << uuid.to_string() << "\n";

    std::cout << (uuid == uuid) << "\n";
    std::cout << (uuid != uuid) << "\n";
    std::cout << (uuid == UUID::gen()) << "\n";
    std::cout << (uuid != UUID::gen()) << "\n";

    return 0;
}