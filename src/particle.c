#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "raylib.h"

void swap_particles(int x_1, int y_1, int x_2, int y_2, int columns, Particle** matrix);

void initialize_matrix(int rows, int columns, Particle* matrix[rows][columns]) {
    for (int x = rows - 1; x > 0; x--) {
        for (int y = columns; y > 0; y--) {
            if ((x % 10 == 0) || (y % 10 == 0)) {
                Particle* particle = new_particle(SAND, YELLOW);
                matrix[x][y] = particle;
            } else {
                // matrix[x][y] = new_particle(SAND, BLUE);
                matrix[x][y] = NULL;
            }
            // matrix[x][y] = NULL;
        }
    }
}

void update_particles(int rows, int columns, Particle** matrix) {
    for (int x = rows-1; x > 0; x--) {
        for (int y = columns-1; y > 0; y--) {
            int index = x*columns + y;
            if (matrix[index] != NULL) {
                switch (matrix[index]->type)
                {
                case SAND:
                    for (int j = -1; j < 2; j++) {
                        if (y+1 > columns) {
                            break;
                        } else if (matrix[x*columns + y + 1] == NULL) {
                            swap_particles(x, y, x, y+1, columns, matrix);
                        }

                        if (x-j < 0 || x-j > rows) {
                            continue;
                        } else {
                            if (matrix[(x-j)*columns + y+1] == NULL) {
                                swap_particles(x, y, x-j, y+1, columns, matrix);
                            }
                        }
                    }

                    break;
                
                default:
                    break;
                }
            }
        }
    }
}

void spawn_particle(int x, int y, int columns, Particle** matrix) {
    // if (matrix[rows][columns] == NULL) {
    //     matrix[rows][columns] = new_particle(SAND, YELLOW);
    //     printf("particle spawned at %d %d\n", rows, columns);
    // }
    if (matrix[x * columns + y] == NULL) {
        matrix[x * columns + y] = new_particle(SAND, YELLOW);
        // printf("particle spawned at %d %d\n", rows, columns);
    }
}

Particle *new_particle(int type, Color color) {
    Particle *particle = (Particle *) malloc(sizeof(Particle));
    particle->type = type;
    particle->color = color;
    return particle;
}

void swap_particles(int x_1, int y_1, int x_2, int y_2, int columns, Particle** matrix) {
    Particle* temp = matrix[x_1 * columns + y_1];
    matrix[x_1 * columns + y_1] = matrix[x_2 * columns + y_2];
    matrix[x_2 * columns + y_2] = temp; 
}