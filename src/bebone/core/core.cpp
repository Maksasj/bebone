#include "core.h"

namespace bebone::core {
    std::string utils_read_file(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;

        ss << file.rdbuf();

        return ss.str();
    }
}
