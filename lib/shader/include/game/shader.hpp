#pragma once

#include <string>

namespace gm {

#ifdef DEBUG
    const std::string SHADER_PATH = "./src/shaders/";
#else
    const std::string SHADER_PATH = "./shaders/";
#endif

const std::string SHADER_VERSION = "#version 330 core\n";

std::string load_shader(std::string filename);

}