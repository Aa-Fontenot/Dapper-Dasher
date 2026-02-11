#include "raylib.h"

int main() {
    const int window_height{512};
    const int window_width{1024};

    InitWindow(window_width, window_height, "Dapper Dasher");

    // rectangle values
    const int width{50};
    const int height{80};
    int posY{window_height - height};
    
    int y_velocity{0};
    int x_velocity{0};
    const int gravity{1};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        //Game Logic Begins
        posY += y_velocity;
        if (posY >= (window_height - height)) { 
            y_velocity = 0;
        } else {
            y_velocity += gravity; 
        }    
        
        // Jump Logic
        if (IsKeyPressed(KEY_SPACE) && posY == window_height - height) {
            y_velocity -=10;
        }

        DrawRectangle(window_width / 2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}