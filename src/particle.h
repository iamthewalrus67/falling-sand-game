#ifndef PARTICLE_H
#define PARTICLE_H
#include "raylib.h"

typedef struct Particle {
    unsigned int type;
    Color color;
    Vector2 velocity;
    bool has_been_updated;
} Particle;

enum PARTICLE_TYPES {SAND, WATER, SOLID};

void initialize_matrix(int rows, int columns, Particle* matrix[rows][columns]);
void spawn_particle(int x, int y, int columns, int type, Particle** matrix);
void update_particles(int rows, int columns, Particle** matrix);
Particle *new_particle(int type, Color color);
void clear_matrix(int rows, int columns, Particle** matrix);
#endif