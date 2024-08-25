#pragma once

#include <string>

class Shader
{
private:

	unsigned int m_id;

public:

	Shader() = delete;
	Shader(unsigned int id);
	~Shader();

	void use() const;

};

