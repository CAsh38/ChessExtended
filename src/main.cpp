#include "include/WindowsSpecific.h"
#include "include/SceneManager.h"
#include "include/Managers.h"
#include <thread>
#include <chrono>
#include <numeric>

typedef std::chrono::duration<double> seconds;

double TPS;
bool EXIT, command_received;
std::vector<std::string> UserDebugInfo, ConsoleDebugInfo;
int ScreenHeight, ScreenWidth;
std::vector<double> TPSArray;
Scene ActualScene;

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
    Info info = Info();
    for (std::string text : ConsoleDebugInfo)
    {
        if (text.contains("TPS"))
        {
            if (text.contains("_A"))
            {
                static int cycles = 0;
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
        if (text.contains("rects"))
        {
            for (const auto& scene_item : ActualScene)
            {
                for (const auto& item : scene_item.Storage)
                {
                    static float thickness = 0;
                    if (command_received) thickness = atoi(strrchr(text.c_str(), '_') + 1);
                    if (std::holds_alternative<TextBox>(item))
                    {
                        TextBox thatBox = std::get<TextBox>(item);
                        thatBox.DrawBorders(thickness, WHITE);
                    }
                    else if (std::holds_alternative<Button>(item))
                    {
                        TextBox thatBox = std::get<Button>(item).Text;
                        thatBox.DrawBorders(thickness, WHITE);
                    }
                }
            }
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
    SceneManager *scenemanager = SceneManager::GetInstance();
    const Scene& MainMenu = scenemanager->GetMainMenu();
    scenemanager->sceneStack.push_back(MainMenu);
    ActualScene = MainMenu;
#ifdef _DEBUG
    std::thread console(RunConsoleInParallel);
#endif
    while (!WindowShouldClose() && EXIT == 0)
    {
        auto frameStart = GET_TIME
        RespondToPlayerInput(ActualScene);
        auto frameEnd = GET_TIME
        seconds frameTime = frameEnd - frameStart;
        TPS = 1 / frameTime.count();
        BeginDrawing();
            ClearBackground(scenemanager->BackGroundColor);
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