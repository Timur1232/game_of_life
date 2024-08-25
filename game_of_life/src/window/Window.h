#pragma once

struct GLFWwindow;
class Events;

class Window
{
private:

	static GLFWwindow* s_window;

public:

	friend Events;

	static int initialize(int width, int height, const char* title);
	static void terminate();

	static bool isShouldClose();
	static void setShouldClose(bool flag);
	static void swapBuffers();

};

