//
// Created by clement on 15/10/2025.
//

#ifndef GAMEOFLIFE_WINDOW_H
#define GAMEOFLIFE_WINDOW_H

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>

#include "model.h"

typedef struct Window {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Window;

Window* GOL_CreateWindow();
void GOL_DestroyWindow(Window*);

bool GOL_GetWindowEvent(SDL_Event*);

void GOL_RenderWindow(const Window*, Model*);

static SDL_FRect GetGameArea();

static void RenderGrid(const Window*);

static void TranslateRectToArea(SDL_FRect*);

void TranslatePointToArea(SDL_FPoint*);

static void RenderCells(const Window*, const Model*);

#endif //GAMEOFLIFE_WINDOW_H