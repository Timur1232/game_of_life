#pragma once

/*_______________________[Consts]_______________________*/

constexpr int WORLD_WIDTH = 100;
constexpr int WORLD_HEIGHT = 50;
constexpr int PIXELS_PER_CEIL = 15;

constexpr int SCREEN_WIDTH = WORLD_WIDTH * PIXELS_PER_CEIL;
constexpr int SCREEN_HEIGHT = WORLD_HEIGHT * PIXELS_PER_CEIL;

constexpr float GRID_TOP = 1.0f;
constexpr float GRID_LEFT = -1.0f;

constexpr int WORLD_SIZE = WORLD_WIDTH * WORLD_HEIGHT;
constexpr int LINES_AMOUNT = WORLD_WIDTH + WORLD_HEIGHT + 2;
constexpr int LINES_FLOATS_AMOUNT = LINES_AMOUNT * 4;

/*_______________________[Types]_______________________*/

using Ceil = bool;

enum State
{
    DEAD = false,
    ALIVE = true
};