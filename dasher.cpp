#include "raylib.h"

struct AnimData {
    Rectangle rec;
    Vector2 pos;
    int frame; 
    float updateTime;
    float runningTime;
}; 








int main() {
    int windowDimensions[2];
    windowDimensions[0] = 1024;
    windowDimensions[1] = 512;

    

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");


   
    
    int y_velocity{0};
    const int gravity_vel{2300};

    // Nebula Creation
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{{0.0, 0.0, nebula.width / 8, nebula.height / 8}, {windowDimensions[0], windowDimensions[1] - nebula.height / 8}, 0, 1.0/20.0, 0.0}; 
    AnimData neb2Data{{0.0, 0.0, nebula.width / 8, nebula.height / 8}, {windowDimensions[0], windowDimensions[1] - (4 *(nebula.height / 8))}, 0, 1.0/12.0, 0.0}; 
    

    AnimData nebulae[2]{ nebData, neb2Data}; 
   

   
    int nebula_vel{-600}; 
  


    // Scarfy Creation
    
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    AnimData scarfyData; 
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height; 
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0; 
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height; 
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 8.0;
    scarfyData.runningTime = 0.0; 


    const int effLowerBound = windowDimensions[1] - scarfyData.rec.height;
    const int jump_vel{-850};

    
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        const float dt{GetFrameTime()};
        BeginDrawing();
        ClearBackground(WHITE);

        //Game Logic Begins
        bool isInAir{scarfyData.pos.y != effLowerBound};
        scarfyData.pos.y += y_velocity * dt;
        if (scarfyData.pos.y >= (effLowerBound)) { 
            y_velocity = 0;
        } else {
            y_velocity += gravity_vel * dt; 
        }
        

        // Animation Logic
        if (isInAir) {
            scarfyData.rec.x = 0;
        }
        if (!isInAir) { //Scarfy Animation
            scarfyData.runningTime += dt;
            if (scarfyData.runningTime >= scarfyData.updateTime) {
                scarfyData.runningTime = 0.0;
            
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame == 6) {
                    scarfyData.frame = 0;
                }
                }
    }

        //Nebula Animation Logic
        nebulae[0].runningTime += dt;
        if (nebulae[0].runningTime >= nebulae[0].updateTime) {
            nebulae[0].runningTime = 0;

            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame >= 8) {
                nebulae[0].frame = 0;
            } 
        }

       nebulae[1].runningTime += dt;
        if (nebulae[1].runningTime >= nebulae[1].updateTime) {
            nebulae[1].runningTime = 0;

            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame >= 8) {
                nebulae[1].frame = 0;
            } 
        }

        // Nebula Logic 
        nebulae[0].pos.x += nebula_vel * dt;
        nebulae[1].pos.x += nebula_vel * dt; 
        
        // Jump Logic
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            y_velocity += jump_vel;
        }
        if (scarfyData.pos.y > effLowerBound) {
            scarfyData.pos.y = effLowerBound;
        }

        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, PURPLE); 

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}