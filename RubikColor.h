#ifndef RUBIKCOLOR_HEADER

#define RUBIKCOLOR_HEADER

#include <iostream>
#include <windows.h>
#include <iomanip>

/// <summary>
/// The colors of the rubik's cube
/// </summary>
enum RubikColor { BLACK = -1, WHITE = 0, GREEN = 1, RED = 2, BLUE = 3, ORANGE = 4, YELLOW = 5 };

/// <summary>
/// The colors used to print in colors in the console. The order can not be changed
/// </summary>
enum ConsoleColor { DARKBLUE_ = 1, DARKGREEN_, DARKTEAL_, DARKRED_, DARKPINK_, DARKYELLOW_, GRAY_, DARKGRAY_, BLUE_, GREEN_, TEAL_, RED_, PINK_ /*ORANGE*/, YELLOW_, WHITE_ };

ConsoleColor translate(RubikColor color);

RubikColor translate(int color);

struct setcolor
{
	ConsoleColor _c;
	HANDLE _console_handle;
	setcolor(RubikColor c, HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE))
		: _c(translate(c)), _console_handle(0)
	{
		_console_handle = console_handle;
	}
};

// We could use a template here, making it more generic. Wide streams won't
// work with this version.
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &s, const setcolor &ref);

#endif