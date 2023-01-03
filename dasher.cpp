#include "raylib\include\raylib.h"


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};




int main()
{
    int wDims[2];
    wDims[0] = 512;
    wDims[1] = 380;
    
    // const int Wwidth{512}, Wheight{380}; // these values dont change in the following code
    const char* title{"Dappy-Dasher"};
    InitWindow(wDims[0], wDims[1], title);

    // float textlength = MeasureText("Hello!", 22);

    //acceleration due to gravity (pixels/freme)/frame
    const int gravity{1'000};
    const int jumpvel{-600}; // in pixels per second
    bool isInAir{false};

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // AnimData for nebula
    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle Rec
        {wDims[0], wDims[1] - nebula.height/8}, // Vector2 Pos
        0, // int frame
        1./12., // float update time
        0. // float running time
    }; 

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},
        {wDims[0] + 300, wDims[1] - nebula.height/8},
        0,
        1./16.,
        0
    };


    // Texture display for animations
    // nebula variables
    // Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    // Vector2 nebPos{wDims[0], Wheight - nebRec.height};

    // Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    // Vector2 neb2Pos{Wwidth + 300, Wheight - nebRec.height};

    // nebula animation variables
    // int nebframe{};
    // const float nebUpdateTime{1./12.};
    // float nebRunningTime{};

    // int neb2frame{};
    // const float neb2UpdateTime{1./16.};
    // float neb2RunningTime{};

    // nebula x velocity
    int nebVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    // AnimData for scarfy
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    
    scarfyData.pos.x = wDims[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = wDims[1] - scarfyData.rec.height;

    scarfyData.frame = 0;

    scarfyData.updateTime = 1./12.;
    scarfyData.runningTime = 0.;

    // Rectangle scarfyRec;
    // scarfyRec.width = scarfy.width/6;
    // scarfyRec.height = scarfy.height;
    // scarfyRec.x = 0;
    // scarfyRec.y = 0;
    // Vector2 scarfyPos;
    // scarfyPos.x = Wwidth/2 - scarfyRec.width/2;
    // scarfyPos.y = Wheight - scarfyRec.height;

    // animation frame
    int frame{}; // initialized to 'zero'
    // amount of time before we update the animation time
    const float updateTime{1.0/12.0};
    float runningTime{};
    
    // // Rectangle Dims
    // const int width{50}, height{80};


    // velocity
    // int posY{Wheight - height};
    int velocity{0};

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // DrawRectangle(Wwidth/2 - width/2, posY, width, height, BLUE);
        // Jump on space
        if (scarfyData.pos.y >= wDims[1] - scarfyData.rec.height)
        {
            //Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else 
        {
            //Rectangle is in the air
            //apply gravity
            velocity += gravity * dT;
            isInAir = true;

        }
        // Check for Jumping
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpvel;
        }
        
        // update nebula position
        nebData.pos.x += nebVel * dT;

        neb2Data.pos.x += nebVel * dT;

        //update scarfy y position
        scarfyData.pos.y += velocity * dT;
        
        // update scarfy's animation
        if (!isInAir)
        {
            // update running time
            runningTime += dT;
            if (runningTime >= updateTime) 
            {
                runningTime = 0;
                // update animation
                scarfyData.rec.x = frame * scarfyData.rec.width;
                frame++;
                if(frame>5)
                {
                    frame = 0;
                }
            }
        }

        // update nebula's animation
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }
        // update nebula's animation
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if(neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        
        
        //draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, WHITE);

        //draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // end drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}