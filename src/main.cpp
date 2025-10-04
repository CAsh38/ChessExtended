#include "include/WindowsSpecific.h"
#include "include/SceneManager.h"
#include "include/Managers.h"
#include "include/Utilities.h"
#include <thread>
#include <chrono>

double TPS;
bool EXIT, command_received;
std::vector<std::string> UserDebugInfo, ConsoleDebugInfo;
int ScreenHeight, ScreenWidth;
std::vector<double> TPSArray;

static double getAverageTPS(int cycles)
{
    if (TPSArray.size() <= cycles) TPSArray.push_back(TPS);
    else if (TPSArray.size() == cycles + 1)
    {
        TPSArray.erase(TPSArray.begin());
        TPSArray.push_back(TPS);
    }
    else TPSArray.erase(TPSArray.begin(), TPSArray.end() - cycles);
    return std::reduce(TPSArray.begin(), TPSArray.end()) / TPSArray.size();
}

static Info GetConsoleDebugInfo()
{
    static int cycles = 0;
    Info info = Info();
    for (std::string text : ConsoleDebugInfo)
    {
        if (text.contains("TPS"))
        {
            if (text.contains("_A"))
            {
                if (command_received) cycles = atoi(strrchr(text.c_str(), '_') + 1);
                info.push_back(getAverageTPS(cycles));
            }
            else info.push_back(TPS);
        }
        if (text == "cursor")
        {
            std::string text = std::to_string(GetMouseX()) + "|" + std::to_string(GetMouseY());
            info.push_back(text);
        }
    }
    command_received = 0;
    return info;
}

static void CheckShouldDisplayDebugInfo()
{
    if (ConsoleDebugInfo.size() == 0) return;
    else DisplayConsoleDebugInfo(GetConsoleDebugInfo());
    return;
}

int main(void)
{
    EXIT = 0, command_received = 0;
    HideConsoleIfNotDebugging();
    InitializeWindow();
    SceneManager scenemanager;
    Scene MainMenu = scenemanager.GetMainMenu(), ActualScene;
    ActualScene = MainMenu;
#ifdef _DEBUG
    std::thread console(RunConsoleInParallel);
#endif
    while (!WindowShouldClose() && EXIT == 0)
    {
        auto frameStart = std::chrono::steady_clock::now();
        RespondToPlayerInput(ActualScene);
        auto frameEnd = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> frameTime = frameEnd - frameStart;
        TPS = 1 / frameTime.count();
        BeginDrawing();
            ClearBackground(BLACK);
            DrawSceneOnScreen(ActualScene);
            CheckShouldDisplayDebugInfo();
        EndDrawing();
    }
#ifdef _DEBUG
    console.join();
#endif
    CloseWindow();
    return 0;
}