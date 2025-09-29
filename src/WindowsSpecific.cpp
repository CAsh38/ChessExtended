#include "include/WindowsSpecific.h"
#include <windows.h>
#undef CloseWindow

void HideConsoleIfNotDebugging()
{
#ifndef _DEBUG
	FreeConsole();
#else
	std::cout << "Entering debugging mode" << std::endl;
#endif
}

void ParseConsoleCommand()
{
#ifndef _DEBUG
	return;
#endif
	std::string command;
	std::getline(std::cin, command);
	char* next_token = NULL, *token = NULL;
	char* data = command.data();
	token = strtok_s(data, BASE_DELIMITATOR, &next_token);
	if (!strcmp(token, "show"))
		ShowCommand(next_token);
	return;
}

static void ShowCommand(char *next_token)
{
	char* token = strtok_s(NULL , BASE_DELIMITATOR, &next_token);
	if (!strcmp(token, "TPS")) 
		std::cout << TPS << std::endl;
	return;
}