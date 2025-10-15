//
// Created by clement on 15/10/2025.
//

#ifndef GAMEOFLIFE_MODEL_H
#define GAMEOFLIFE_MODEL_H

#define GRID_SIZE 50
#define GAME_SIZE 1000
#define CELL_SIZE (GAME_SIZE / GRID_SIZE)

typedef struct Cell {
    bool alive;
    int x;
    int y;
} Cell;

typedef struct Model {
    Cell grid[GRID_SIZE][GRID_SIZE];
} Model;

Model* GOL_CreateModel();
void GOL_DestroyModel(Model*);

void GOL_ResetModel(Model *);

#endif //GAMEOFLIFE_MODEL_H