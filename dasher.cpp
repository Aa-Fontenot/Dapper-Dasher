#include "raylib.h"

int main() {
    const int window_height{512};
    const int window_width{1024};

    

    InitWindow(window_width, window_height, "Dapper Dasher");


   
    
    int y_velocity{0};
    int x_velocity{0};
    const int gravity_vel{2300};

    // Scarfy Creation
    
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec; 
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos; 
    scarfyPos.x = window_width / 2 - scarfyRec.width / 2;
    scarfyPos.y = window_height - scarfyRec.height; 

    int frame{};
    float updateTime{1.0 / 8.0};
    float runningTime{}; 

    const int effLowerBound = window_height - scarfyRec.height;
    const int jump_vel{-750};

    
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        const float dt{GetFrameTime()};
        BeginDrawing();
        ClearBackground(WHITE);

        
        // Animation Logic
        runningTime += dt;
        if (runningTime >= updateTime) {
            runningTime = 0.0;
        
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame == 6) {
                frame = 0;
            }
        }


        //Game Logic Begins
        bool isInAir{scarfyPos.y != effLowerBound};
        scarfyPos.y += y_velocity * dt;
        if (scarfyPos.y >= (effLowerBound)) { 
            y_velocity = 0;
        } else {
            y_velocity += gravity_vel * dt; 
        }    
        
        // Jump Logic
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            y_velocity += jump_vel;
        }
        if (scarfyPos.y > effLowerBound) {
            scarfyPos.y = effLowerBound;
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}