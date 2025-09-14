#include "Definitions.h"

int main(void)
{
    InitializeWindow();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(100, 100, 200, 200, RED);
        DrawFPS(10, 10);
        /*DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);*/
        EndDrawing();
    }
    CloseWindow();
    return 0;
}