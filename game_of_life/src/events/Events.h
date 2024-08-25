#pragma once

using uint = unsigned int;

class Events
{
public:

	static bool* s_keys;
	static uint* s_frames;
	static uint s_current;
	static float s_deltaX;
	static float s_deltaY;
	static float s_x;
	static float s_y;
	static bool s_cursorLoked;
	static bool s_cursorStarted;

	static int initialize();
	static void pullIvents();

	static bool keyPressed(int keycode);
	static bool keyJPressed(int keycode);

	static bool mousePressed(int button);
	static bool mouseJPressed(int button);

};

