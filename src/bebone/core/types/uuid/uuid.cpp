#include "uuid.h"

namespace bebone::core {
    UUID::UUID(const u64& data1, const u64& data2) {
            data[0] = data1;
            data[1] = data2;
        }

    UUID::UUID() {
        *this = UUID(0, 0);
    }

    bool UUID::operator==(const UUID& other) const {
        return this->data[0] == other.data[0] && this->data[1] == other.data[1];
    }

    bool UUID::operator!=(const UUID& other) const {
        return !(*this == other);
    }

    std::string UUID::to_string() const {
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(16) << data[0];
        ss << std::hex << std::setfill('0') << std::setw(16) << data[1];

        std::string tmp = ss.str();
        tmp.insert(8, "-");
        tmp.insert(13, "-");
        tmp.insert(18, "-");
        tmp.insert(23, "-");

        return tmp;
    }

    UUID UUID::gen() {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());

        static std::uniform_int_distribution<u64> dist(0ULL, std::numeric_limits<u64>::max());

        return UUID(dist(gen), dist(gen));
    }
}
