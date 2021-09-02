#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "raylib.h"

#define GRAVITY 10;

void swap_particles(int, int, Particle**);
void free_particle(int, int, int, Particle**);
void reset_has_been_updated(int, int, Particle**);

// Initialize matrix at start (not used for now)
void initialize_matrix(int rows, int columns, Particle* matrix[rows][columns]) {
    for (int x = rows - 1; x > 0; x--) {
        for (int y = columns; y > 0; y--) {
            if ((x % 10 == 0) || (y % 10 == 0)) {
                Particle* particle = new_particle(SAND, YELLOW);
                matrix[x][y] = particle;
            } else {
                matrix[x][y] = NULL;
            }
        }
    }
}

void clear_matrix(int rows, int colums, Particle** matrix) {
    for (int x = rows-1; x > 0; x--) {
        for (int y = colums-1; y > 0; y--) {
            free_particle(x, y, colums, matrix);
        }
    }
}

// Update particle position every frame
void update_particles(int rows, int columns, Particle** matrix) {
    for (int x = rows-1; x > 0; x--) {
        for (int y = columns-1; y > 0; y--) {
            int index = x*columns + y;
            if ((matrix[index] != NULL) && !matrix[index]->has_been_updated) {
                int new_index = -1;

                switch (matrix[index]->type)
                {
                case SAND:
                    if (y+1 > columns-1) {
                        matrix[index]->has_been_updated = true;
                        break;
                    }
                    
                    if ((matrix[x*columns + y+1] == NULL) || (matrix[x*columns + y+1]->type == WATER)) {
                        new_index = x*columns + y+1;
                    } // Check if down-left cell is empty
                    else if ((x-1 >= 0) && ((matrix[(x-1)*columns + y+1] == NULL) || (matrix[(x-1)*columns + y+1]->type) == WATER)) {
                        new_index = (x-1)*columns + y+1;
                    // Check if down-right cell is empty
                    } else if ((x+1 < rows) && ((matrix[(x+1)*columns + y+1] == NULL) || (matrix[(x+1)*columns + y+1]->type == WATER))) {
                        new_index = (x+1)*columns + y+1;
                    }

                    break;
                case WATER:
                    if (y+1 < columns) {
                        if (matrix[x*columns + y+1] == NULL) {
                            new_index = x*columns + y+1;
                        } else if ((x-1 >= 0) && (matrix[(x-1)*columns + y+1] == NULL)) {
                            new_index = (x-1)*columns + y+1;
                        } else if ((x+1 < rows) && (matrix[(x+1)*columns + y+1] == NULL)) {
                            new_index = (x+1)*columns + y+1;
                        }

                        if (new_index != -1) {
                            break;
                        }
                    }
                    
                    if ((x-1 >= 0) && (matrix[(x-1)*columns + y] == NULL)) {
                        new_index = (x-1)*columns + y;
                    } else if ((x+1 < rows) && (matrix[(x+1)*columns + y] == NULL)) {
                        new_index = (x+1)*columns + y;
                    }

                    break;
                
                default:
                    break;
                }


                if (new_index != -1) {
                        swap_particles(index, new_index, matrix);
                        matrix[new_index]->has_been_updated = true;
                } else {
                    matrix[index]->has_been_updated = true;
                }
            }
        }
    }
    reset_has_been_updated(rows, columns, matrix);
}


// Set has_been_updated variable in all particles to false
void reset_has_been_updated(int rows, int columns, Particle** matrix) {
    for (int x = rows-1; x > 0; x--) {
        for (int y = columns-1; y > 0; y--) {
            if (matrix[x*columns + y] != NULL) {
                matrix[x*columns + y]->has_been_updated = false;
            }
        }
    }
}

// Spawn particle in (x, y)
void spawn_particle(int x, int y, int columns, int type, Particle** matrix) {
    if (matrix[x * columns + y] == NULL) {
        Color color;
        switch (type)
        {
        case SAND:
            color = YELLOW;
            break;
        case WATER:
            color = BLUE;
            break;
        case SOLID:
            color = BROWN;
            break;
        default:
            color = WHITE;
        }
        matrix[x * columns + y] = new_particle(type, color);
    }
}


// Returns pointer to Particle (used only in this module)
Particle* new_particle(int type, Color color) {
    Particle *particle = (Particle *) malloc(sizeof(Particle));
    particle->type = type;
    particle->color = color;
    particle->has_been_updated = false;
    particle->velocity = (Vector2) {0, 0};
    return particle;
}

// Delete particle from matrix
void free_particle(int x, int y, int columns, Particle** matrix) {
    free(matrix[x*columns + y]);
    matrix[x*columns + y] = NULL;
}

// Swap particles in the matrix (used only in this module)
void swap_particles(int current_index, int new_index, Particle** matrix) {
    Particle* temp = matrix[current_index];
    matrix[current_index] = matrix[new_index];
    matrix[new_index] = temp; 
}