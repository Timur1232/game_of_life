#pragma once

#include <string>

class Shader;

extern Shader* load_shader(std::string vertex_file, std::string fragment_file);
