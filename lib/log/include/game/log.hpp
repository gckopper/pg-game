#pragma once

#include <glad/glad.h>

#ifdef DEBUG 
#define LOG(X) std::cerr << X << std::endl; 
#else
#define LOG(X) 
#endif

namespace gm {
    void terminate();
}
