#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include "../config.h"

class Shader;

class GameWorld
{
private:

	Ceil m_world[WORLD_SIZE] = { 0 };
	Ceil m_world_buffer[WORLD_SIZE] = { 0 };
	int m_aliveCeils = 0;
	GLfloat m_grid[LINES_FLOATS_AMOUNT] = { 0.0f };

public:

	GameWorld();
	GameWorld(const std::vector<glm::ivec2>& ceils);

	void renderAll();
	void applyRules();

	void pushCeil(glm::ivec2 pos);
	void popCeil(glm::ivec2 pos);
	bool checkCeil(glm::ivec2 pos);
	void loadWorld(const std::vector<glm::ivec2>& world);
};

glm::ivec2 interpolite_mouse_pos(float x, float y);

