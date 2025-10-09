#include "include/WindowsSpecific.h"
#include <windows.h>
#include <winuser.h>
#undef CloseWindow

void HideConsoleIfNotDebugging()
{
#ifndef _DEBUG
	FreeConsole();
#else
	std::cout << "Entering debugging mode" << std::endl;
#endif
}

static void ShowCommand(char* next_token)
{
	char* token = strtok_s(NULL, BASE_DELIMITATOR, &next_token);
	if (GetPosInStr(token, '-') != 0)
	{
		bool ok = 1;
		char* modificators = token;
		std::string text = {};
		token = strtok_s(NULL, BASE_DELIMITATOR, &next_token);
		char* object = token;
		try
		{
			if (token == NULL) throw "Specify the object!";
			else text += token;
			for (int i = 1; i < strlen(modificators); i++)
			{
				if (modificators[i] == 'a')
				{
					token = strtok_s(NULL, BASE_DELIMITATOR, &next_token);
					if (token == NULL) throw "Specify number of cycles!";
					else text = text + "_A_" + token;
				}
				else if (modificators[i] == 's') ok = 0;
			}
			if (strstr(token, "rects") != NULL)
			{
				token = strtok_s(NULL, BASE_DELIMITATOR, &next_token);
				if (token == NULL) throw "Specify thickness";
				text = text + "_" + token;
			}
		}
		catch (std::string error) { THROW(error); }
		for (int i = 0; i < ConsoleDebugInfo.size(); i++)
		{
			if (strstr(ConsoleDebugInfo.at(i).c_str(), object) != NULL)
				ConsoleDebugInfo.erase(ConsoleDebugInfo.begin() + i);
		}
		if (ok) ConsoleDebugInfo.push_back(text);
		else if (CmpStrings(object, "TPS"))
			TPSArray.erase(TPSArray.begin(), TPSArray.end());
		/*ConsoleDebugInfo.erase(std::remove(ConsoleDebugInfo.begin(), ConsoleDebugInfo.end(), object),
			ConsoleDebugInfo.end());*/
	}
	else if (CmpStrings(token, "TPS"))
		std::cout << TPS << std::endl;
	else if (CmpStrings(token, "cursor"))
	{
		POINT pos;
		bool result = GetCursorPos(&pos);
		std::cout << "Cursor:" << pos.x << "|" << pos.y << std::endl;
	}
	return;
}

void ParseConsoleCommand()
{
	std::string command;
	std::getline(std::cin, command);
	char* data = command.data();
	if (strcmp(data, ""))
	{
		command_received = 1;
		char* next_token = NULL, * token = NULL;
		token = strtok_s(data, BASE_DELIMITATOR, &next_token);
		if (CmpStrings(token, "show"))
			ShowCommand(next_token);
		else if (CmpStrings(token, "exit"))
			EXIT = 1;
	}
	return;
}

void RunConsoleInParallel()
{
	bool flag = 1;
	while (flag)
	{
		ParseConsoleCommand();
		if (EXIT == 1) flag = 0;
	}
}
