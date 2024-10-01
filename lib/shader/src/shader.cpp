#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include <game/shader.hpp>

#include <game/log.hpp>

std::string gm::load_shader(std::string filename) {
    std::ifstream file(SHADER_PATH + filename, std::ios_base::ate);

    if (!file.is_open()) {
        LOG("Failed to open file " << filename);
        LOG("Are you running the program from the correct location?");
        terminate();
    }

    std::string result(SHADER_VERSION.size() + file.tellg(), ' ');
    std::copy(SHADER_VERSION.begin(), SHADER_VERSION.end(), result.begin());
    file.seekg(0);
    file.read(result.data() + SHADER_VERSION.size(), result.size() - SHADER_VERSION.size());

    return result;
}
