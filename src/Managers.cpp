#include "include/Managers.h"
#include <json/json.h>

void StartUpManager()
{
	int result = MakeDirectory("./configs"); // returns 0 if directory already exists
	std::ifstream checkFile("./configs/general.json", std::ios::binary);
	bool verdict = (!checkFile.good() || (checkFile.peek() == std::ifstream::traits_type::eof()));
	checkFile.close();
	if (verdict)
	{
		Json::Value outRoot;
		outRoot["FPS"] = "60";
		int monitorID = GetCurrentMonitor();
		int width = GetMonitorWidth(monitorID), height = GetMonitorHeight(monitorID);
		std::string Resolution = std::to_string(width) + "x" + std::to_string(height);
		outRoot["ScreenSize"] = Resolution;
		outRoot["WindowMode"] = "Fullscreen"; // Options: Windowed / Fullscreen / 35% x 50%

		Json::StreamWriterBuilder builder;
		builder["commentStyle"] = "None";
		builder["indentation"] = "  ";

		std::ofstream file("./configs/general.json", std::ios::out | std::ios::trunc);
		Json::StreamWriter* jsonwriter = builder.newStreamWriter();
		jsonwriter->write(outRoot, &file);
		outRoot.clear();
		file.close();
	}
}

void InitializeWindow()
{
	InitWindow(0, 0, WINDOW_NAME);
	StartUpManager();
	std::ifstream file("./configs/general.json", std::ifstream::binary);
	std::string errs;
	Json::Value root;
	Json::CharReaderBuilder reader;
	bool result = Json::parseFromStream(reader, file, &root, &errs);
	file.close();
	int fps = std::stoi(root["FPS"].asString());
	SetTargetFPS(fps);
	if (strcmp(root["WindowMode"].asString().c_str(), "Fullscreen"))
	{
		std::string Size = root["ScreenSize"].asString();
		const char* size = Size.c_str();
		ScreenHeight = atoi(strchr(size, 'x') + 1);
		Size[Size.find('x')] = '\0';
		ScreenWidth = atoi(size);
		SetWindowSize(ScreenWidth, ScreenHeight);
	}
	else ToggleFullscreen();
	root.clear();
}

void DisplayConsoleDebugInfo(Info info)
{
	int box_width = 0;
	int box_count = 0;
	int width = 0;
	std::string text;
	for (std::string data : ConsoleDebugInfo)
	{
		if (data.contains("TPS"))
		{
			box_width = MAIN_MENU_BUTTON_WIDTH;
			double n = std::get<double>(info[box_count]);
			text = std::to_string(n);
			text = "TPS:" + text;
		}
		if (data == "cursor")
		{
			box_width = MAIN_MENU_BUTTON_WIDTH;
			text = std::get<std::string>(info[box_count]);
			text = data + ":" + text;
		}
		width = ScreenWidth - box_width;
		DrawText(text.c_str(), width, (box_count+1) * MAIN_MENU_BUTTON_HEIGHT,
			DEBUG_TEXT_FONT_SIZE, WHITE);
		box_count++;
	}
}