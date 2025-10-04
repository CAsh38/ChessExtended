#pragma once

#define WINDOW_NAME "ChessExtended"
#define PLAY_BUTTON_POSY (double)300
#define MAIN_MENU_BUTTON_WIDTH (double)150
#define MAIN_MENU_BUTTON_HEIGHT (double)30
#define MAIN_MENU_BUTTON_FONT_SIZE 30
#define DEBUG_TEXT_FONT_SIZE 20
#define MAIN_MENU_BUTTON_FONT (std::string)"Aria Math"
#define BASE_DELIMITATOR " "
#define GetPosInStr(a,b) strchr((a), (b)) 
#define CmpStrings(a,b) !strcmp((a), (b)) // returns true if strings are equal
#define GetTps(a) CLOCKS_PER_SEC / (double)(clock() - (a));
#define THROW(a) std::cout << (a) << std::endl;