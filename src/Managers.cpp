#include "include/Defines.h"
#include "include/Managers.h"

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
	if (root["WindowMode"].asString() != "Fullscreen")
	{
		std::string Size = root["ScreenSize"].asString();
		const char* size = Size.c_str();
		int H = atoi(strchr(size, 'x') + 1);
		Size[Size.find('x')] = '\0';
		int W = atoi(size);
		SetWindowSize(W, H);
	}
	else ToggleFullscreen();
	root.clear();
}