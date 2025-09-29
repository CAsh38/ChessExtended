#include "include/Managers.h"
#include "include/WindowsSpecific.h"
#include "include/SceneManager.h"

double TPS;

int main(void)
{
    HideConsoleIfNotDebugging();
    InitializeWindow();
    SceneManager scenemanager;
    Scene MainMenu = scenemanager.GetMainMenu(), ActualScene;
    ActualScene = MainMenu;
    clock_t start; double end;

    while (!WindowShouldClose())
    {
        start = clock();
        BeginDrawing();
            DrawSceneOnScreen(ActualScene);
        EndDrawing();
        RespondToPlayerInput(ActualScene);
        end = (double)(clock() - start) / CLOCKS_PER_SEC;
        TPS = 1 / end;
        ParseConsoleCommand();
    }
    CloseWindow();
    return 0;
}