#pragma once

#include <glm/glm.hpp>

class Line
{
private:

	glm::ivec2 m_start;
	glm::ivec2 m_end;

public:

	Line(glm::ivec2 start, glm::ivec2 end);

	glm::vec2 interpolitePos(int width, int height);

};

