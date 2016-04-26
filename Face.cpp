#include "Face.h"


Face::Face(int number, RubikColor color) {
	this->number = number;
	this->color = color;
}

void Face::setNumber(int number) {
	if (this->number == -1)
		this->number = number;
}

void Face::setLocked(bool value)  
{ 
	isLockedPosition = value; 
}