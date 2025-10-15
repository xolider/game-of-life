//
// Created by clement on 15/10/2025.
//

#include "game.h"
#include <stdlib.h>
#include "util.h"
#include <SDL3/SDL_timer.h>

Game* GOL_CreateGame(Window *w) {

    Game *game = malloc(sizeof(Game));
    game->window = w;
    game->running = false;
    game->model = GOL_CreateModel();

    return game;
}

void GOL_DestroyGame(Game *g) {
    GOL_DestroyModel(g->model);
    free(g);
}

void GOL_GameStart(Game* game) {
    game->running = true;
    last_time = SDL_GetPerformanceCounter();
    double timer = 0;
    bool iterate = false;
    while (game->running) {
        SDL_Event ev;
        while (GOL_GetWindowEvent(&ev)) {
            switch (ev.type) {
                case SDL_EVENT_QUIT:
                    game->running = false;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    SDL_FPoint p = {ev.button.x, ev.button.y};
                    TranslatePointToArea(&p);
                    ToggleCellAlive(game, p);
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (ev.key.key == SDLK_SPACE) {
                        iterate = !iterate;
                    } else if (ev.key.key == SDLK_R) {
                        iterate = false;
                        GOL_ResetModel(game->model);
                    }
                    break;
            }
        }

        double delta = GetDeltaTime();
        timer += (delta / 1000.0);

        if (timer >= 0.1) {
            if (iterate) GameIterate(game);
            timer = 0;
        }

        GOL_RenderWindow(game->window, game->model);
    }
}

static void ToggleCellAlive(Game *g, SDL_FPoint p) {
    if (p.x < 0 || p.y < 0 || p.x >= GAME_SIZE || p.y >= GAME_SIZE) return;
    int cell_x = (int)p.x / CELL_SIZE;
    int cell_y = (int)p.y / CELL_SIZE;
    Cell c = g->model->grid[cell_x][cell_y];
    c.alive = !c.alive;
    g->model->grid[cell_x][cell_y] = c;
}

static void GameIterate(Game* g) {
    GOL_LOG_DEBUG("Iterate");

    Cell grid_cpy[GRID_SIZE][GRID_SIZE];
    memcpy(grid_cpy, g->model->grid, sizeof(Cell) * GRID_SIZE * GRID_SIZE);

     for (int i = 0; i < GRID_SIZE; i++) {
         for (int j = 0; j < GRID_SIZE; j++) {
             Cell cell = grid_cpy[i][j];

             Cell neighbors[8];
             unsigned int size;
             GetNeighbors(grid_cpy, &cell, neighbors, &size);

             int alive_neighbor_number = 0;
             for (int n = 0; n < size; n++) {
                 alive_neighbor_number += neighbors[n].alive;
             }

             if (alive_neighbor_number == 3) {
                 cell.alive = true;
             }
             if (alive_neighbor_number < 2 || alive_neighbor_number > 3) {
                 cell.alive = false;
             }
             g->model->grid[i][j] = cell;
         }
     }
}

/**
 *
 * @return An array of all neighbors cells
 */
static void GetNeighbors(Cell grid[GRID_SIZE][GRID_SIZE], Cell *cell, Cell neighbors_out[8], unsigned int *size_out) {
    int size_tmp = 0;
    if (cell->x > 0) {
        neighbors_out[size_tmp++] = grid[cell->x-1][cell->y];
        if (cell->y > 0) {
            neighbors_out[size_tmp++] = grid[cell->x-1][cell->y-1];
        }
        if (cell->y < GRID_SIZE-1) {
            neighbors_out[size_tmp++] = grid[cell->x-1][cell->y+1];
        }
    }
    if (cell->x < GRID_SIZE-1) {
        neighbors_out[size_tmp++] = grid[cell->x+1][cell->y];
        if (cell->y > 0) {
            neighbors_out[size_tmp++] = grid[cell->x+1][cell->y-1];
        }
        if (cell->y < GRID_SIZE-1) {
            neighbors_out[size_tmp++] = grid[cell->x+1][cell->y+1];
        }
    }
    if (cell->y > 0) {
        neighbors_out[size_tmp++] = grid[cell->x][cell->y-1];
    }
    if (cell->y < GRID_SIZE-1) {
        neighbors_out[size_tmp++] = grid[cell->x][cell->y+1];
    }

    *size_out = size_tmp;
}

static double GetDeltaTime() {
    unsigned long now = SDL_GetPerformanceCounter();
    double delta = (double)(now - last_time) * 1000.0 / (double)SDL_GetPerformanceFrequency();
    last_time = now;
    return delta;
}