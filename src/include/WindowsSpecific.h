#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Defines.h"

extern std::vector<std::string> ConsoleDebugInfo;
extern std::vector<double> TPSArray;
extern double TPS;
extern bool EXIT, command_received;

void HideConsoleIfNotDebugging();
void ParseConsoleCommand();
void RunConsoleInParallel();