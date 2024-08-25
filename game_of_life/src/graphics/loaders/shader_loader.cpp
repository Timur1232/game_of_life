#include "shader_loader.h"
#include "..\Shader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>


Shader* load_shader(std::string vertex_file, std::string fragment_file)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {
        vShaderFile.open(vertex_file);
        fShaderFile.open(fragment_file);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        std::cerr << e.what() << std::endl;
        return nullptr;
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "SHADER::VERTEX: Compilation failed" << std::endl;
        std::cerr << infoLog << std::endl;
        glDeleteShader(vertex);
        return nullptr;
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "SHADER::FRAGMENT: Compilation failed" << std::endl;
        std::cerr << infoLog << std::endl;
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return nullptr;
    }

    GLuint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "SHADER::PROGRAM: Linking failed" << std::endl;
        std::cerr << infoLog << std::endl;
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(id);
        return nullptr;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return new Shader(id);
}