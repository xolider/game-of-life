//
// Created by clement on 15/10/2025.
//

#ifndef GAMEOFLIFE_GAME_H
#define GAMEOFLIFE_GAME_H

#include "window.h"

typedef struct Game {
    Window *window;
    bool running;
    Model *model;
} Game;

Game* GOL_CreateGame(Window*);
void GOL_DestroyGame(Game*);

void GOL_GameStart(Game*);

static void ToggleCellAlive(Game*, SDL_FPoint);

static void GameIterate(Game*);

static void GetNeighbors(Cell grid[GRID_SIZE][GRID_SIZE], Cell *cell, Cell neighbors_out[8], unsigned int *size_out);

static double GetDeltaTime();

static unsigned long last_time;

#endif //GAMEOFLIFE_GAME_H