#include <iostream>
#include <vector>
#include <chrono>

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


/*GLuint indices[] = {
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

	// Цвет фона
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	bool pause = true;

	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();

	// Основной цикл
	while (!Window::isShouldClose()) {

		start = std::chrono::system_clock::now();

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
			if (Events::keyJPressed(GLFW_KEY_3)) {
				game.loadWorld(star);
			}
			if (Events::keyJPressed(GLFW_KEY_4)) {
				game.loadWorld(pong);
			}
			if (Events::keyJPressed(GLFW_KEY_5)) {
				game.loadWorld(pulse);
			}
			if (Events::keyJPressed(GLFW_KEY_6)) {
				game.loadWorld(rod);
			}
			if (Events::keyJPressed(GLFW_KEY_7)) {
				game.loadWorld(core);
			}
			if (Events::keyJPressed(GLFW_KEY_8)) {
				game.loadWorld(space_ship);
			}
			if (Events::keyJPressed(GLFW_KEY_N)) {
				game.applyRules();
			}
			if (Events::keyJPressed(GLFW_KEY_S)) {
				game.saveWorld();
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		// Рендер текущего кадра
		game.renderAll();

		// Расчет следующего кадра
		if (!pause)
			game.applyRules();

		Window::swapBuffers();

		end = std::chrono::system_clock::now();

		std::chrono::duration<double> duration = end - start;
		double fps = 1 / duration.count();
		std::string stringFPS = std::to_string(fps);
		glfwSetWindowTitle(Window::s_window, stringFPS.c_str());
		// std::cout << fps << std::endl;
	}

	Renderer::terminate();
	Window::terminate();
}