#include "RubikColor.h"

// We could use a template here, making it more generic. Wide streams won't
// work with this version.
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &s, const setcolor &ref)
{
	SetConsoleTextAttribute(ref._console_handle, ref._c);
	return s;
}

RubikColor translate(int color) {
	return static_cast<RubikColor>(color);
}

ConsoleColor translate(RubikColor color) {
	switch (color) {
		case RubikColor::WHITE:
			return ConsoleColor::WHITE_;
		case RubikColor::GREEN:
			return ConsoleColor::GREEN_;
		case RubikColor::RED:
			return ConsoleColor::RED_;
		case RubikColor::BLUE:
			return ConsoleColor::BLUE_;
		case RubikColor::ORANGE:
			return ConsoleColor::PINK_; //Orange not available
		case RubikColor::YELLOW:
			return ConsoleColor::YELLOW_;
	}

	return ConsoleColor::WHITE_;
	
}