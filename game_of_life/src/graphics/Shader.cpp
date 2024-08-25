#include "Shader.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Shader::Shader(unsigned int id) : m_id(id) {}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::use() const
{
	glUseProgram(m_id);
}
