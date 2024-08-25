#include "game_rules.h"
#include "../config.h"

int get_new_state(Ceil* ceil, int pos)
{
    int neighbours = 0;
    int x = pos % WORLD_WIDTH,
        y = pos / WORLD_WIDTH;

    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            neighbours += ceil[get_pos(x + i, y + j)];
        }

    if (ceil[pos]) {
        if (neighbours >= 2 && neighbours <= 3) return ALIVE;
        else return DEAD;
    }
    else
        if (neighbours == 3) return ALIVE;
}

int get_pos(int x, int y)
{
    if (x >= 0 && y >= 0 && x < WORLD_WIDTH && y < WORLD_HEIGHT)
        return x + y * WORLD_WIDTH;

    if (x < 0) {
        if (y < 0) return WORLD_SIZE - 1;
        if (y >= WORLD_HEIGHT) return WORLD_WIDTH - 1;
        return (y + 1) * WORLD_WIDTH - 1;
    }
    if (x >= WORLD_WIDTH) {
        if (y < 0) return WORLD_SIZE - WORLD_WIDTH - 2;
        if (y >= WORLD_HEIGHT) return 0;
        return y * WORLD_WIDTH;
    }
    if (y < 0) {
        y = WORLD_HEIGHT - 1;
        return x + y * WORLD_WIDTH;
    }
    return x;
}


