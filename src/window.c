//
// Created by clement on 15/10/2025.
//

#define WINDOW_SIZE 1200

#include "window.h"
#include <stdlib.h>

#include "util.h"

Window* GOL_CreateWindow() {
    Window *win = malloc(sizeof(Window));
    win->window = SDL_CreateWindow("Game of Life", WINDOW_SIZE, WINDOW_SIZE, 0);

    if (!win->window) {
        return nullptr;
    }

    win->renderer = SDL_CreateRenderer(win->window, nullptr);
    if (!win->renderer) {
        GOL_LOG_ERROR("Could not create renderer");
        SDL_DestroyWindow(win->window);
        return nullptr;
    }

    SDL_SetRenderVSync(win->renderer, 1);

    return win;
}

void GOL_DestroyWindow(Window *window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
}

bool GOL_GetWindowEvent(SDL_Event* ev) {
    return SDL_PollEvent(ev);
}

void GOL_RenderWindow(const Window* window, Model* model) {
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(window->renderer);
    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    RenderGrid(window);
    RenderCells(window, model);

    SDL_RenderPresent(window->renderer);
}

static SDL_FRect GetGameArea() {
    float x = (float)(WINDOW_SIZE - GAME_SIZE) / 2.0f;
    float y = x;
    return (SDL_FRect) {x, y, GAME_SIZE, GAME_SIZE};
}

static void RenderGrid(const Window *window) {
    SDL_FRect area = GetGameArea();
    for (int i = 0; i <= GAME_SIZE; i += CELL_SIZE) {
        SDL_RenderLine(window->renderer, (float)i+area.x, area.y,
            (float)i+area.x, GAME_SIZE+area.y);
    }
    for (int i = 0; i <= GAME_SIZE; i += CELL_SIZE) {
        SDL_RenderLine(window->renderer, area.x, (float)i+area.y,
            GAME_SIZE+area.x, (float)i+area.y);
    }
}

static void TranslateRectToArea(SDL_FRect* src) {
    SDL_FRect area = GetGameArea();
    src->x += area.x;
    src->y += area.y;
}

static void RenderCells(const Window *win, const Model *model) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Cell cell = model->grid[i][j];
            SDL_FRect rect = {((float)cell.x * CELL_SIZE)+1, ((float)cell.y * CELL_SIZE)+1,
                CELL_SIZE-1, CELL_SIZE-1};
            TranslateRectToArea(&rect);

            if (cell.alive) {
                SDL_SetRenderDrawColor(win->renderer, 125, 255, 125, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(win->renderer, &rect);
                SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            }
        }
    }
}

void TranslatePointToArea(SDL_FPoint* p) {
    SDL_FRect area = GetGameArea();
    p->x -= area.x;
    p->y -= area.y;
}