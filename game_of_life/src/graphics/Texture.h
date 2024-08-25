#pragma once

#include <string>

class Texture
{
private:

	unsigned int m_id;
	int m_width;
	int m_height;

public:

	Texture() = delete;
	Texture(unsigned int id, int width, int height);
	~Texture();

	void bind() const;

};

