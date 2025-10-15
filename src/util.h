//
// Created by clement on 15/10/2025.
//

#ifndef GAMEOFLIFE_UTIL_H
#define GAMEOFLIFE_UTIL_H

#include <SDL3/SDL_log.h>

#define GOL_LOG_DEBUG(log) SDL_Log("[DEBUG] %s\n", log)
#define GOL_LOG_ERROR(log) SDL_Log("[ERROR] %s : %s\n", log, SDL_GetError())

#endif //GAMEOFLIFE_UTIL_H