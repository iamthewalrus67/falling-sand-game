#ifndef PARTICLE_H
#define PARTICLE_H
#include "raylib.h"

typedef struct Particle {
    unsigned int type;
    Color color;
} Particle;

enum PARTICLE_TYPES {SAND};

void initialize_matrix(int rows, int columns, Particle* matrix[rows][columns]);
void spawn_particle(int x, int y, int columns, Particle** matrix);
void update_particles(int rows, int columns, Particle** matrix);
Particle *new_particle(int type, Color color);
#endif