//
// Created by clement on 15/10/2025.
//

#ifndef GAMEOFLIFE_WINDOW_H
#define GAMEOFLIFE_WINDOW_H

#ifndef ROBOTO_TTF_PATH
    #error "ROBOTO_TTF_PATH must point to a Roboto .ttf file"
#endif

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "model.h"

typedef struct Window {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    TTF_TextEngine *engine;
} Window;

Window* GOL_CreateWindow();
void GOL_DestroyWindow(Window*);

bool GOL_GetWindowEvent(SDL_Event*);

void GOL_RenderWindow(const Window*, Model*, bool);

static SDL_FRect GetGameArea();

static void RenderGrid(const Window*);

static void TranslateRectToArea(SDL_FRect*);

void TranslatePointToArea(SDL_FPoint*);

static void RenderCells(const Window*, const Model*);

static void RenderPlayingStatus(const Window*, bool);

#endif //GAMEOFLIFE_WINDOW_H