#include "CornerFace.h"


CornerFace::CornerFace(int number, RubikColor color) : Face(number, color)
{

}

int CornerFace::getPieceNumber() {
	return this->number % 8;
}