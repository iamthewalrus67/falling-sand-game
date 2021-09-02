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

    int particle_size = 3;
    int matrix_width = screen_width/particle_size;
    int matrix_height = screen_height/particle_size;
    int brush_size[] = {1, 1};

    Particle *matrix[matrix_width][matrix_height];
    int current_particle_type = SAND;
    memset(matrix, (int)0, matrix_width * matrix_height * sizeof(Particle *));


    SetTargetFPS(300);
    int tick = 0;

    while (!WindowShouldClose()) {
        // Update
        if (tick++ == 1) {
            update_particles(matrix_width, matrix_height, &matrix[0][0]);
            tick = 0;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            spawn_particle((int)mouse_pos.x/particle_size, (int)mouse_pos.y/particle_size, matrix_height, current_particle_type, &matrix[0][0]);

            for (int x = 0; x < brush_size[0]; x++) {
                for (int y = 0; y < brush_size[1]; y++) {
                    if (((int)mouse_pos.x/particle_size-x >= 0) && ((int)mouse_pos.x/particle_size-x < matrix_width) && ((int)mouse_pos.y/particle_size-y >= 0) && ((int)mouse_pos.y/particle_size-y < matrix_height) && (matrix[x][y] == NULL)) {
                        spawn_particle((int)mouse_pos.x/particle_size-x, (int)mouse_pos.y/particle_size-y, matrix_height, current_particle_type, &matrix[0][0]);
                    }
                }
            }
        }
        if (IsKeyPressed(KEY_ONE)) {
            current_particle_type = SAND;
        }
        if (IsKeyPressed(KEY_TWO)) {
            current_particle_type = WATER;
        }
        if (IsKeyPressed(KEY_THREE)) {
            current_particle_type = SOLID;
        }
        if (IsKeyDown(KEY_E)) {
            brush_size[0]++;
            brush_size[1]++;
        }
        if (IsKeyDown(KEY_Q)) {
            brush_size[0]--;
            brush_size[1]--;
        }
        if (IsKeyPressed(KEY_R)) {
            clear_matrix(matrix_width, matrix_height, &matrix[0][0]);
        }
        


        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            Vector2 mouse_pos = GetMousePosition();
            DrawRectangleLines((int)mouse_pos.x-brush_size[0]*particle_size, (int)mouse_pos.y - brush_size[1]*particle_size, brush_size[0]*particle_size, brush_size[1]*particle_size, RED);


            for (int x = matrix_width - 1; x > 0; x--) {
                for (int y = matrix_height - 1; y > 0; y--) {
                    if ((x*particle_size < screen_width) && (y*particle_size < screen_height) && (matrix[x][y] != NULL)) {
                        DrawRectangle(x*particle_size, y*particle_size, particle_size, particle_size, matrix[x][y]->color);
                    }
                }
            }
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
