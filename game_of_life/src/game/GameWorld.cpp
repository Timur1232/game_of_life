#include "GameWorld.h"

#include <GL/glew.h>
#include <string.h>
#include <iostream>

#include "../renderer/Renderer.h"
#include "../graphics/Shader.h"

#include "../graphics/loaders/shader_loader.h"
#include "game_rules.h"
#include "../config.h"

static float pixel_interpolation(int a, int ceil)
{
	return ((float)a / ceil) * 2.0f - 1.0f;
}

GameWorld::GameWorld() : m_aliveCeils(0) 
{
	memset(m_world, false, WORLD_SIZE * sizeof(Ceil));
	memset(m_world_buffer, false, WORLD_SIZE * sizeof(Ceil));

	float x = GRID_LEFT;
	float y = GRID_TOP;

	float shiftX = 1.0f + pixel_interpolation(PIXELS_PER_CEIL, SCREEN_WIDTH);
	float shiftY = 1.0f + pixel_interpolation(PIXELS_PER_CEIL, SCREEN_HEIGHT);


	for (int i = 0; i < WORLD_WIDTH * 4; i += 4) {
		m_grid[i] = x;
		m_grid[i + 1] = GRID_TOP - shiftY * WORLD_HEIGHT;
		m_grid[i + 2] = x;
		m_grid[i + 3] = GRID_TOP;
		x += shiftX;
	}

	for (int i = WORLD_WIDTH * 4; i < LINES_FLOATS_AMOUNT; i += 4) {
		m_grid[i] = GRID_LEFT;
		m_grid[i + 1] = y;
		m_grid[i + 2] = GRID_LEFT + shiftX * WORLD_WIDTH;
		m_grid[i + 3] = y;
		y -= shiftY;
	}

	Renderer::fillStaticBuffer(LINES_FLOATS_AMOUNT, m_grid);
}

GameWorld::GameWorld(const std::vector<glm::ivec2>& ceils) : GameWorld()
{
	int pos;
	for (const glm::ivec2& ceil : ceils) {
		pos = (ceil.y - 1) * WORLD_WIDTH + ceil.x - 1;
		m_world[pos] = true;
	}
	m_aliveCeils = ceils.size();
}

void GameWorld::renderAll()
{
	if (m_aliveCeils) {
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		const std::vector<GLuint> fixed_indices = {
				0, 1, 2,
				0, 2, 3
		};

		float x = GRID_LEFT;
		float y = GRID_TOP;
		float shiftX = pixel_interpolation(PIXELS_PER_CEIL, SCREEN_WIDTH) + 1.0f;
		float shiftY = pixel_interpolation(PIXELS_PER_CEIL, SCREEN_HEIGHT) + 1.0f;

		for (int i = 0, j = 0; i < WORLD_SIZE; i++) {
			if (m_world[i]) {
				//std::cout << i << '\n';
				x = pixel_interpolation((i % WORLD_WIDTH) * PIXELS_PER_CEIL, SCREEN_WIDTH);
				y = -pixel_interpolation((i / WORLD_WIDTH) * PIXELS_PER_CEIL, SCREEN_HEIGHT);

				vertices.push_back(x);
				vertices.push_back(y);

				vertices.push_back(x + shiftX);
				vertices.push_back(y);

				vertices.push_back(x + shiftX);
				vertices.push_back(y - shiftY);

				vertices.push_back(x);
				vertices.push_back(y - shiftY);

				for (GLuint a : fixed_indices) {
					indices.push_back(a + 4 * j);
				}
				j++;
			}
		}
		/*for (GLfloat i : vertices)
			std::cout << i << ", ";
		std::cout << std::endl;
		for (GLuint i : indices)
			std::cout << i << ", ";
		std::cout << std::endl;*/
		Renderer::renderBoxes(m_aliveCeils, vertices.data(), indices.data());
	}
	Renderer::renderLines();
}

void GameWorld::applyRules()
{
	int newAlive = 0;
	for (int i = 0; i < WORLD_SIZE; i++) {
		m_world_buffer[i] = get_new_state(m_world, i);
	}
	for (int i = 0; i < WORLD_SIZE; i++) {
		m_world[i] = m_world_buffer[i];
		if (m_world_buffer[i]) newAlive++;
	}
	m_aliveCeils = newAlive;
}

void GameWorld::pushCeil(glm::ivec2 pos)
{
	int ipos = (pos.y - 1) * WORLD_WIDTH + (pos.x - 1);
	if (!m_world[ipos]) {
		m_world[ipos] = true;
		m_aliveCeils++;
	}
}

void GameWorld::popCeil(glm::ivec2 pos)
{
	int ipos = (pos.y - 1) * WORLD_WIDTH + (pos.x - 1);
	if (m_world[ipos]) {
		m_world[ipos] = false;
		m_aliveCeils--;
	}
}

bool GameWorld::checkCeil(glm::ivec2 pos)
{
	int ipos = (pos.y - 1) * WORLD_WIDTH + (pos.x - 1);
	return m_world[ipos];
}

void GameWorld::loadWorld(const std::vector<glm::ivec2>& world)
{
	memset(m_world, false, WORLD_SIZE * sizeof(Ceil));
	memset(m_world_buffer, false, WORLD_SIZE * sizeof(Ceil));

	int pos;
	for (const glm::ivec2& ceil : world) {
		pos = (ceil.y - 1) * WORLD_WIDTH + ceil.x - 1;
		m_world[pos] = true;
	}
	m_aliveCeils = world.size();
}

glm::ivec2 interpolite_mouse_pos(float x, float y)
{
	int new_x = WORLD_WIDTH * (x / SCREEN_WIDTH) + 1;
	int new_y = WORLD_HEIGHT * (y / SCREEN_HEIGHT) + 1;
	return glm::ivec2(new_x, new_y);
}
