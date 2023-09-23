#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <fstream>
#include <sstream>

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

#endif
