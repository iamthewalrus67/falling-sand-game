#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "raylib.h"
#include <string.h>

int main(void) {
    // Screen size
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width, screen_height, "Test Game");

    int particle_size = 5;
    int matrix_width = screen_width/particle_size;
    int matrix_height = screen_height/particle_size;

    Particle *cell_matrix[matrix_width][matrix_height];
    memset(cell_matrix, (int)0, matrix_width * matrix_height * sizeof(Particle *));
    // initialize_matrix(matrix_width, matrix_height, cell_matrix);

    SetTargetFPS(300);
    int tick = 0;

    int x_pos = 0;
    int y_pos = 0;

    while (!WindowShouldClose()) {
        // Update
        // tick++;
        // if (tick == 1) {
        //     Vector2 mouse_pos = GetMousePosition();
        //     // printf("Integer mouse pos devided by %d: %d %d\n", particle_size, (int)mouse_pos.x / particle_size, (int)mouse_pos.y / 5);
        //     // printf("%d %d\n", (int) mouse_pos.x / particle_size, (int) mouse_pos.y / particle_size);
        //     // spawn_particle((int)mouse_pos.x / particle_size, (int)mouse_pos.y / particle_size, cell_matrix);
        //     // spawn_particle(mouse_pos.x, mouse_pos.y, cell_matrix);
        //     // cell_matrix[x_pos++][y_pos++] = new_particle(SAND, RED);
        //     // printf("%d %d\n", (int)mouse_pos.x, (int)mouse_pos.y);
        //     spawn_particle((int)mouse_pos.x/particle_size, (int)mouse_pos.y/particle_size, cell_matrix);
        //     // printf("spawned particle at %d %d\n", x_pos, y_pos);

        //     tick = 0;
        // }
        if (tick++ == 10) {
            // printf("Updating\n");
            update_particles(matrix_width, matrix_height, cell_matrix);
            tick = 0;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            spawn_particle((int)mouse_pos.x/particle_size, (int)mouse_pos.y/particle_size, matrix_height, &cell_matrix[0][0]);
        }


        // Draw
        BeginDrawing();
            ClearBackground(BLACK);

            for (int x = matrix_width - 1; x > 0; x--) {
                for (int y = matrix_height - 1; y > 0; y--) {
                    if ((x*particle_size < screen_width) && (y*particle_size < screen_height) && (cell_matrix[x][y] != NULL)) {
                    //     // printf("Particle position:%d %d\n", x, y);
                    //     // DrawRectangle(x*particle_size, y*particle_size, particle_size, particle_size, cell_matrix[x][y]->color);
                    //     // printf("Rendered particle at %d %d\n", x*particle_size, y*particle_size);
                    //     // printf("Particle found at x = %d\n", x);
                    //     // printf("Drawing particle at %d %d\n", x, y);
                    //     // DrawRectangle(x*particle_size-particle_size, y*particle_size-particle_size, particle_size, particle_size, cell_matrix[x][y]->color);
                    //     DrawRectangle(x, y, 1, 1, cell_matrix[x][y]->color);
                        DrawRectangle(x*particle_size-particle_size, y*particle_size-particle_size, particle_size, particle_size, cell_matrix[x][y]->color);
                    }
                    // if ((x*particle_size > screen_width) || (y*particle_size > screen_height)) {
                    //     continue;
                    // } else if (cell_matrix[x][y] != NULL) {
                    //     DrawRectangle(x*particle_size-particle_size, y*particle_size-particle_size, particle_size, particle_size, cell_matrix[x][y]->color);
                    // }
                }
            }
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
