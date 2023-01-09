#include "raylib\include\raylib.h"


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround( AnimData data, int windowHeight){
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame){
    // update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime) 
    {
        data.runningTime = 0.;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame) 
        {
            data.frame = 0;
        }
    }
    return data;
}


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
    // AnimData nebData{
    //     {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle Rec
    //     {wDims[0], wDims[1] - nebula.height/8}, // Vector2 Pos
    //     0, // int frame
    //     1./12., // float update time
    //     0. // float running time
    // }; 

    // AnimData neb2Data{
    //     {0.0, 0.0, nebula.width/8, nebula.height/8},
    //     {wDims[0] + 300, wDims[1] - nebula.height/8},
    //     0,
    //     1./16.,
    //     0
    // };

    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae]{};
    
    for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = wDims[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.;
        nebulae[i].updateTime = 0.;
        nebulae[i].pos.x = wDims[0] + 300*i;
    }




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


    float finishLine{ nebulae[sizeOfNebulae - 1].pos.x};

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

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // scroll bg
        bgX -= 20 * dT;
        if (bgX <= -background.width*2) {
            bgX = 0.;
        }
        // scroll mg
        mgX -= 40 * dT;
        if (mgX <= -midground.width*2) {
            mgX = 0.;
        }
        // scroll fg
        fgX -= 80 * dT;
        if (fgX <= -foreground.width*2) {
            fgX = 0.;
        }

        // draw backgroung
        Vector2 bg1Pos{bgX, 0.0};
        Vector2 bg2Pos{bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg1Pos, 0., 2., WHITE);
        DrawTextureEx(background, bg2Pos, 0., 2., WHITE);

        Vector2 mg1Pos{mgX, 0.0};
        Vector2 mg2Pos{mgX + midground.width*2, 0.0};
        DrawTextureEx(midground, mg1Pos, 0., 2., WHITE);
        DrawTextureEx(midground, mg2Pos, 0., 2., WHITE);

        Vector2 fg1Pos{fgX, 0.0};
        Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0., 2., WHITE);
        DrawTextureEx(foreground, fg2Pos, 0., 2., WHITE);






        // DrawRectangle(Wwidth/2 - width/2, posY, width, height, BLUE);
        // Jump on space
        if (isOnGround(scarfyData, wDims[1]))
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

        for (int i = 0; i < sizeOfNebulae; i++) {
            // update the pos of each nebulae
            nebulae[i].pos.x += nebVel * dT;       
        }

        // Update finish Line
        finishLine += nebVel * dT;

        //update scarfy y position
        scarfyData.pos.y += velocity * dT;
        
        // update scarfy's animation
        if (!isInAir)
        {

            scarfyData = updateAnimData(scarfyData, dT, 5);

            // // update running time
            // runningTime += dT;
            // if (runningTime >= updateTime) 
            // {
            //     runningTime = 0;
            //     // update animation
            //     scarfyData.rec.x = frame * scarfyData.rec.width;
            //     frame++;
            //     if(frame>5)
            //     {
            //         frame = 0;
            //     }
            // }
        }
        
        for (int i = 0; i < sizeOfNebulae; i++) {

            nebulae[i] = updateAnimData(nebulae[i], dT, 7);


            // // update nebula's animation
            // nebulae[i].runningTime += dT;
            // if (nebulae[i].runningTime >= nebulae[0].updateTime)
            // {
            //     nebulae[i].runningTime = 0.;
            //     nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
            //     nebulae[i].frame++;
            //     if(nebulae[i].frame > 7)
            //     {
            //         nebulae[i].frame = 0;
            //     }
            // }        
        }

        
        
        //draw nebula
        for (int i = 0; i < sizeOfNebulae; i++) {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }



        //draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // end drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(foreground);
    UnloadTexture(midground);
    CloseWindow();
}