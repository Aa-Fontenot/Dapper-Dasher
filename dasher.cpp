#include "raylib.h"

int main() {
    const int window_height{512};
    const int window_width{1024};

    InitWindow(window_width, window_height, "Dapper Dasher");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        //Game Logic Begins




        EndDrawing();
    }
    CloseWindow();
}