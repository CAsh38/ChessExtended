#pragma once
#include "Defines.h"
#include "Foundations.h"
#include <fstream>

extern std::vector<std::string> UserDebugInfo, ConsoleDebugInfo;
extern int ScreenHeight, ScreenWidth;

void StartUpManager();
void InitializeWindow();
void DisplayConsoleDebugInfo(Info);