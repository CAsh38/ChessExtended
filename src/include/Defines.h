#pragma once
#define WINDOW_NAME "ChessExtended"
#define BASE_WINDOW_SIZE_X 50
#define BASE_WINDOW_SIZE_y 35
#define PLAY_BUTTON_POSY (double)300
#define MAIN_MENU_BUTTON_WIDTH (double)150
#define MAIN_MENU_BUTTON_HEIGHT (double)30
#define MAIN_MENU_BUTTON_FONT_SIZE 30
#define MAIN_MENU_BUTTON_FONT (std::string)"Aria Math"
#define BASE_DELIMITATOR " "
#define GetPosInStr(a,b) strchr((a), (b))

int ExitApp()
{
	exit(0);
}