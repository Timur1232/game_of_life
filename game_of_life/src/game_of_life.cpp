#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "graphics/Shader.h"
#include "window/Window.h"
#include "events/Events.h"
#include "renderer/Renderer.h"
#include "game/GameWorld.h"

#include "graphics/loaders/shader_loader.h"

#include "config.h"
#include "game/StartConfig.h"

/*GLfloat vert1[] = {
		-1, 0.96, -0.96, 0.96, -0.96, 0.92, -1, 0.92, -0.96, 0.96, -0.92, 0.96, -0.92, 0.92, -0.96, 0.92, -0.92, 0.96, -0.88, 0.96, -0.88, 0.92, -0.92, 0.92
};

GLuint indices[] = {
		0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11
};

GLfloat vertices[] = {
	//   x	   y
	   -1.0f, 1.0f,
		-0.96f, 1.0f,
	   -0.96f, 0.96f,
		-1.0f, 0.96f
};

GLuint rec[] = {
		0, 1, 2,
		0, 2, 3
};*/


int main()
{
	// Создание и инициализация окна
	if (Window::initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Govno 2.0")) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Инициализация системы событий
	Events::initialize();

	// Инициализация системы рендера
	try {
		Renderer::initialize();
	} catch (const char* e) {
		std::cerr << "Failed to initialize Renderer" << std::endl;
		std::cerr << e << std::endl;
		Window::terminate();
		return -1;
	}

	// Основной объект игрового поля
	GameWorld game;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	bool pause = true;

	// Основной цикл
	while (!Window::isShouldClose()) {
		Events::pullIvents();

		// Обработка событий (нажатий клавиш и мыши)
		if (Events::keyJPressed(GLFW_KEY_ESCAPE)) {
			Window::setShouldClose(true);
		}
		if (Events::keyJPressed(GLFW_KEY_SPACE)) {
			pause = pause ? false : true;
		}
		if (pause) {
			if (Events::mousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
				game.pushCeil(interpolite_mouse_pos(Events::s_x, Events::s_y));
			}
			if (Events::mousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
				game.popCeil(interpolite_mouse_pos(Events::s_x, Events::s_y));
			}
			if (Events::keyJPressed(GLFW_KEY_1)) {
				game.loadWorld(empty);
			}
			if (Events::keyJPressed(GLFW_KEY_2)) {
				game.loadWorld(rifle);
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		// Рендер текущего кадра
		game.renderAll();

		// Расчет следующего кадра
		if (!pause)
			game.applyRules();

		Window::swapBuffers();
	}

	Renderer::terminate();
	Window::terminate();
}