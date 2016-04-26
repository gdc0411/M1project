#include "MiddleFace.h"

MiddleFace::MiddleFace(int index, RubikColor color): Face(index, color) {
	this->number = index;
	this->color = color;
	this->isLockedPosition = index;
}