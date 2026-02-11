#include "raylib.h"

int main() {
    const int window_height{512};
    const int window_width{1024};

    InitWindow(window_width, window_height, "Dapper Dasher");

    // rectangle values
    const int width{50};
    const int height{80};
    const int effLowerBound{window_height - height};
    int posY{effLowerBound};
    const int jump_velocity{-22};
    
    int y_velocity{0};
    int x_velocity{0};
    const int gravity{1};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        //Game Logic Begins
        bool isInAir{posY != effLowerBound};
        posY += y_velocity;
        if (posY >= (effLowerBound)) { 
            y_velocity = 0;
        } else {
            y_velocity += gravity; 
        }    
        
        // Jump Logic
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            y_velocity += jump_velocity;
        }
        if (posY > effLowerBound) {
            posY = effLowerBound;
        }

        DrawRectangle(window_width / 2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}