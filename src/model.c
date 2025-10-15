//
// Created by clement on 15/10/2025.
//

#include "model.h"
#include <stdlib.h>

Model* GOL_CreateModel() {
    Model *model = malloc(sizeof(Model));
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Cell cell = {
                .alive = false,
                .x = i,
                .y = j
            };
            model->grid[i][j] = cell;
        }
    }
    return model;
}
void GOL_DestroyModel(Model* m) {
    free(m);
}

void GOL_ResetModel(Model *model) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            model->grid[i][j].alive = false;
        }
    }
}