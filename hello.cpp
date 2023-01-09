// #include "raylib.h" // use this to match the project with the tut
#include "raylib-4.2.0_win64_mingw-w64\include\raylib.h"

int main() 
{   
    // Make the window 
    int Wwidth{800};
    int Wheight{450};
    const char* title = "Axe Game";
    InitWindow( Wwidth, Wheight, title);


    // Circle info
    int Circle_X = 200; //Wwidth/2; //used to be
    int Circle_Y = 200; //Wheight/2;//used to be
    int Circle_R = 25;

    // Circle Edge info
    int l_circle_x{Circle_X - Circle_R};
    int r_circle_x{Circle_X + Circle_R};
    int u_circle_y{Circle_Y - Circle_R};
    int b_circle_y{Circle_Y + Circle_R};

    // Rectangle info or axe info
    int axe_X{400}, axe_Y{0};
    int axe_dim{50};
    // int axe_W{50}, axe_H{50};
    // Axe Edge info
    int l_axe_x{axe_X};
    int r_axe_x{axe_X + axe_dim};
    int u_axe_y{axe_Y};
    int b_axe_y{axe_Y + axe_dim};

    int direction{10}; 
    
    bool collision_with_axe = 
                            (b_axe_y >= u_circle_y) && 
                            (u_axe_y <= b_circle_y) && 
                            (l_axe_x <= r_circle_x) && 
                            (r_axe_x >= l_circle_x);
    

    SetTargetFPS(30);
    while (WindowShouldClose() == false) //or use != true
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe) {
            DrawText("GAME OVER!", 400 - 75, 200, 20, RED);
        }
        else {
                //Game Logic Begins

                // Update the edges
                l_circle_x = Circle_X - Circle_R;
                r_circle_x = Circle_X + Circle_R;
                u_circle_y = Circle_Y - Circle_R;
                b_circle_y = Circle_Y + Circle_R;

                l_axe_x = axe_X;
                r_axe_x = axe_X + axe_dim;
                u_axe_y = axe_Y;
                b_axe_y = axe_Y + axe_dim;

                collision_with_axe = 
                            (b_axe_y >= u_circle_y) && 
                            (u_axe_y <= b_circle_y) && 
                            (l_axe_x <= r_circle_x) && 
                            (r_axe_x >= l_circle_x);


                DrawCircle(Circle_X, Circle_Y, Circle_R, BLUE);
                DrawRectangle(axe_X, axe_Y, axe_dim, axe_dim, RED);

                // Move the Axe Down
                // axe_Y = axe_Y + 10;
                axe_Y += direction; // same exact thing as the line above

                if (axe_Y > Wheight - 50 || axe_Y == 0)
                {
                    direction = -direction;
                }

                // Move the circle right and left
                if (IsKeyDown(KEY_D) && Circle_X + Circle_R < Wwidth)
                {
                    Circle_X += 10;
                }
                if (IsKeyDown(KEY_A) && Circle_X - Circle_R > 0)
                {
                    Circle_X -= 10;
                }
                // Game Logic Ends

        }
        EndDrawing();
        
    }
}

/*
Floats and Doubles can hold numbers but Floats are memory
efficient and doubles are more precise
*/