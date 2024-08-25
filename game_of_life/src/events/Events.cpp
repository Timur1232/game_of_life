#include "Events.h"
#include "../window/Window.h"
#include <GLFW\glfw3.h>
#include <string.h>

bool* Events::s_keys;
uint* Events::s_frames;
uint Events::s_current = 0;
float Events::s_deltaX = 0.0f;
float Events::s_deltaY = 0.0f;
float Events::s_x = 0.0f;
float Events::s_y = 0.0f;
bool Events::s_cursorLoked = false;
bool Events::s_cursorStarted = false;

constexpr int KEYS_SIZE = 1032;
constexpr int MOUSE_BUTTONS = 1024;

void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	if (Events::s_cursorStarted) {
		Events::s_deltaX += x_pos - Events::s_x;
		Events::s_deltaY += y_pos - Events::s_y;
	}
	else {
		Events::s_cursorStarted = true;
	}
	Events::s_x = x_pos;
	Events::s_y = y_pos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	int index = MOUSE_BUTTONS + button;

	if (action == GLFW_PRESS) {
		Events::s_keys[index] = true;
		Events::s_frames[index] = Events::s_current;
	}
	else if (action == GLFW_RELEASE) {
		Events::s_keys[index] = false;
		Events::s_frames[index] = Events::s_current;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) {
		Events::s_keys[key] = true;
		Events::s_frames[key] = Events::s_current;
	}
	else if (action == GLFW_RELEASE) {
		Events::s_keys[key] = false;
		Events::s_frames[key] = Events::s_current;
	}
}

int Events::initialize()
{
	GLFWwindow* window = Window::s_window;
	s_keys = new bool[KEYS_SIZE];
	s_frames = new uint[KEYS_SIZE];

	memset(s_keys, false, KEYS_SIZE * sizeof(bool));
	memset(s_frames, 0, KEYS_SIZE * sizeof(uint));

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	return 0;
}

void Events::pullIvents()
{
	s_current++;
	s_deltaX = 0.0f;
	s_deltaY = 0.0f;
	glfwPollEvents();
}

bool Events::keyPressed(int keycode)
{
	if (keycode < 0 || keycode >= MOUSE_BUTTONS)
		return false;
	return s_keys[keycode];
}

bool Events::keyJPressed(int keycode)
{
	if (keycode < 0 || keycode >= MOUSE_BUTTONS)
		return false;
	return s_keys[keycode] && s_frames[keycode] == s_current;
}

bool Events::mousePressed(int button)
{
	int index = MOUSE_BUTTONS + button;
	return s_keys[index];
}

bool Events::mouseJPressed(int button)
{
	int index = MOUSE_BUTTONS + button;
	return s_keys[index] && s_frames[index] == s_current;
}

