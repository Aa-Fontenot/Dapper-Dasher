#include "raylib.h"

struct AnimData {
    Rectangle rec;
    Vector2 pos;
    int frame; 
    float updateTime;
    float runningTime;
}; 


bool isOnGround(AnimData data, int windowHeight) {
    return data.pos.y >= windowHeight - data.rec.height; 
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame) {
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime) {
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame ++;
        if (data.frame >= maxFrame) {
            data.frame = 0;
        }

    } return data;
}



int main() {
    int windowDimensions[2];
    windowDimensions[0] = 1024;
    windowDimensions[1] = 512;

    

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");


   
    
    int y_velocity{0};
    const int gravity_vel{2300};

    // Nebula Creation
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    

    AnimData nebulae[6]{}; 
    const int sizeOfNebulae{6};


    for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0; 
        nebulae[i].pos.x = windowDimensions[0] + i * 450;
    }
   
    int nebula_vel{-600}; 


    float finishLine{ nebulae[sizeOfNebulae - 1].pos.x};
  


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


    //Backgrounds

    Texture2D background = LoadTexture("textures/far-buildings.png"); 
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float bgX{};
    float mgX{};
    float fgX{};
    bool collision{}; 


    
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        const float dt{GetFrameTime()}; //Delta Time
        BeginDrawing();
        ClearBackground(WHITE);

        // Background Animation
        bgX -= 20 * dt;
        if (bgX <= -background.width * 4) {
            bgX = 0.0;
        }
        mgX -= 40 * dt;
        if (mgX <= -midground.width * 2.7) {
            mgX = 0.0;
        }
        fgX -= 80 * dt;
        if (fgX <= -foreground.width * 2.7) {
            fgX = 0.0;
        }
        Vector2 bg1Pos{bgX, 0.0};
        Vector2 bg2Pos{bgX + background.width * 4, 0.0};
        Vector2 mg1Pos{mgX, 0.0};
        Vector2 mg2Pos{mgX + midground.width * 2.7, 0.0};
        Vector2 fg1Pos{fgX, 0.0};
        Vector2 fg2Pos{fgX + foreground.width * 2.7, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 4, WHITE);
        DrawTextureEx(background, bg2Pos, 0.0, 4, WHITE);
        DrawTextureEx(midground, mg1Pos, 0.0, 2.7, WHITE);
        DrawTextureEx(midground, mg2Pos, 0.0, 2.7, WHITE);
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.7, WHITE);
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.7, WHITE);
    

        //Game Logic Begins
        bool isInAir{scarfyData.pos.y != effLowerBound};
        scarfyData.pos.y += y_velocity * dt;
        if (isOnGround(scarfyData, windowDimensions[1])) { 
            y_velocity = 0;
        } else {
            y_velocity += gravity_vel * dt; 
        }
        
        // Finish Line Logic
        finishLine += nebula_vel * dt;

        // Collision Logic

        for (AnimData nebula : nebulae) {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec)){
                collision = true;
            }
        }

        // Animation Logic
        if (isInAir) {
            scarfyData.rec.x = 0;
        }
        if (!isInAir) { //Scarfy Animation
            scarfyData = updateAnimData(scarfyData, dt, 6);
    }

        //Nebula Animation Logic
        for (int i = 0; i < sizeOfNebulae; i++) {
        
        nebulae[i] = updateAnimData(nebulae[i], dt, 8); 
    }


        // Nebula Logic 
        for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].pos.x += nebula_vel * dt;
        }
        
        // Jump Logic
        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            y_velocity += jump_vel;
        }
        if (scarfyData.pos.y > effLowerBound) {
            scarfyData.pos.y = effLowerBound;
        }
        // Draw Entities + Win/Lose 
        if (collision == true) {
            DrawText("Game Over!", windowDimensions[0]/2, windowDimensions[1]/2, 52, RED);
        } else if (scarfyData.pos.x >= finishLine) {
            DrawText("You Win!", windowDimensions[0]/2, windowDimensions[1]/2, 52, GREEN); 
        } else {
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        for (int i = 0; i < sizeOfNebulae; i++) {
        DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
    }

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}