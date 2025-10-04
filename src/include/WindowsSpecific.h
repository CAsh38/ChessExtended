#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Defines.h"

extern std::vector<std::string> ConsoleDebugInfo;
extern double TPS;
extern bool EXIT, command_received;

void HideConsoleIfNotDebugging();
void ParseConsoleCommand();
void RunConsoleInParallel();