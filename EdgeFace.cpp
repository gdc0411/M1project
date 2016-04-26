#include "EdgeFace.h"


EdgeFace::EdgeFace(int number, RubikColor color) : Face(number, color)
{

}

int EdgeFace::getPieceNumber() {
	return this->number % 12;
}