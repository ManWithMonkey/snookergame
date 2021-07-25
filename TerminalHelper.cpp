#include "TerminalHelper.h"

void Terminal::ClearHard(){
	system("clear");
}

void Terminal::ClearSoft(){
	std::cout << "\e[3J\e[1;1H";
}
