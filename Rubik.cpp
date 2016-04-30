#include "Rubik.h"

bool Rubik::debug = false;

int Rubik::lines[9][12] = {
	{ -1, -1, -1, 6, 4, 7, -1, -1, -1, -1, -1, -1 },
	{ -1, -1, -1, 6, 1, 7, -1, -1, -1, -1, -1, -1 },
	{ -1, -1, -1, 16, 12, 9, -1, -1, -1, -1, -1, -1 },
	{ 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22 },
	{ 23, 3, 15, 3, 0, 1, 13, 4, 10, 22, 5, 11 },
	{ 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12 },
	{ -1, -1, -1, 10, 14, 19, -1, -1, -1, -1, -1, -1 },
	{ -1, -1, -1, 8, 2, 9, -1, -1, -1, -1, -1, -1 },
	{ -1, -1, -1, 4, 5, 5, -1, -1, -1, -1, -1, -1 }
};

Rubik::Rubik(std::vector<std::vector<int>>& piecesColors) {
	initCornersAndEdges(piecesColors);
	initMovesDictionaryAndFunctions();
}

Rubik::Rubik(int pieces[]) 	
{
	initCornersAndEdges(pieces);
	initMovesDictionaryAndFunctions();
}

Rubik::~Rubik() {
	for (int i = 0; i < 24; i++) {
		delete this->corners[i];
		delete this->edges[i];
	}
	for (int i = 0; i < 6; i++) {
		delete this->middle[i];
	}
	this->moves.clear();
}

void Rubik::initMovesDictionaryAndFunctions() {
	movesDictionary[_R] = _R;	movesFunctions[_R] = &Rubik::R;
	movesDictionary[_Ri] = _Ri;	movesFunctions[_Ri] = &Rubik::Ri;
	movesDictionary[_R2] = _R2;	movesFunctions[_R2] = &Rubik::R2;

	movesDictionary[_L] = _L;	movesFunctions[_L] = &Rubik::L;
	movesDictionary[_Li] = _Li;	movesFunctions[_Li] = &Rubik::Li;
	movesDictionary[_L2] = _L2;	movesFunctions[_L2] = &Rubik::L2;

	movesDictionary[_U] = _U;	movesFunctions[_U] = &Rubik::U;
	movesDictionary[_Ui] = _Ui;	movesFunctions[_Ui] = &Rubik::Ui;
	movesDictionary[_U2] = _U2;	movesFunctions[_U2] = &Rubik::U2;

	movesDictionary[_B] = _B;	movesFunctions[_B] = &Rubik::B;
	movesDictionary[_Bi] = _Bi; movesFunctions[_Bi] = &Rubik::Bi;
	movesDictionary[_B2] = _B2; movesFunctions[_B2] = &Rubik::B2;

	movesDictionary[_F] = _F;	movesFunctions[_F] = &Rubik::F;
	movesDictionary[_Fi] = _Fi;	movesFunctions[_Fi] = &Rubik::Fi;
	movesDictionary[_F2] = _F2;	movesFunctions[_F2] = &Rubik::F2;

	movesDictionary[_D] = _D;	movesFunctions[_D] = &Rubik::D;
	movesDictionary[_Di] = _Di;	movesFunctions[_Di] = &Rubik::Di;
	movesDictionary[_D2] = _D2;	movesFunctions[_D2] = &Rubik::D2;
}

struct Offset Rubik::getOffset(int face) {
	struct Offset offset;
	switch (face) {
	case 0:
		offset.x = 3; offset.y = 0; break;
	case 1:
		offset.x = 0; offset.y = 3;	break;
	case 2:
		offset.x = 3; offset.y = 3;	break;
	case 3:
		offset.x = 6; offset.y = 3;	break;
	case 4:
		offset.x = 9; offset.y = 3;	break;
	case 5:
		offset.x = 3; offset.y = 6;	break;
	default:
		offset.x = 0; offset.y = 0;	break;
	}
	return offset;
}


void Rubik::initCornersAndEdges(std::vector<std::vector<int>>& colors) {

	//Initialization
	struct Offset offset;
	offset.x = 0;
	offset.y = 0;

	int size = colors.size();
	for (int i = 0; i < size; i++) { //For each layer
		int nbPieces = colors[i].size();
		for (int j = 0; j < nbPieces; j++) { //For each piece in this layer

			//Finds coordinates to use
			offset = getOffset(i);
			int x = j;
			int y = 0;
			while (x > 2) {
				x -= 3;
				y++;
			}
			x += offset.x;
			y += offset.y;

			//Determines Edge/Middle/Corner
			//We're only adding the colors as we don't have the # of the pieces yet. We can compute them only once all the colors are added.
			if (j % 2 != 0) { //Edge
				addEdgeColor(Rubik::lines[y][x], ::translate(colors[i][j]));
			}
			else if (j == 4) { //Middle
				addMiddleColor(Rubik::lines[y][x], ::translate(colors[i][j]));
			}
			else { //Corner
				addCornerColor(Rubik::lines[y][x], ::translate(colors[i][j]));
			}
		}
	}

	//Computes the piece # according to the given colors
	initAllFacesNumbersFromColors();
}

void Rubik::initAllFacesNumbersFromColors() {
	//Initializes Middles
		//Already done

	//Initializes Edges
	initAllEdgesNumbersFromColors();

	//Initializes Corners
	initAllCornersNumbersFromColors();
}


void Rubik::initAllEdgesNumbersFromColors() {
	int modulo = 12;
	for (int i1 = 0; i1 < modulo; i1++) //Iterates from edge piece 0 to edge piece 12
	{
		computeEdgePieceNumbersFromColors(i1);
	}
}

void Rubik::computeEdgePieceNumbersFromColors(int i1) {
	i1 = i1 % 12; //Retries the smallest index from this pieces (In case of the piece 0,12 returns 0)
	int i2 = i1 + 12;

	//Find the possible indexes for each individual piece
	std::vector<int> number1 = getPossibleEdgeNumbersFromColor(this->edges[i1]->getColor());
	std::vector<int> number2 = getPossibleEdgeNumbersFromColor(this->edges[i2]->getColor());

	//Find the two indexes that match (modulo 12)
	int size1 = number1.size();
	int size2 = number2.size();
	for (int a = 0; a < size1; a++) {
		for (int b = 0; b < size2; b++) {
			if (number1[a] % 12 == number2[b] % 12) {
				this->edges[i1]->setNumber(number1[a]);
				this->edges[i2]->setNumber(number2[b]);
				return;
			}
		}
	}
	error("error finding egde from colors");
}

std::vector<int> Rubik::getPossibleEdgeNumbersFromColor(RubikColor color) {
	switch (color) {
	case RED:
		return std::vector<int>{0, 1, 2, 3};
	case GREEN:
		return std::vector<int>{15, 18, 20, 23};
	case YELLOW:
		return std::vector<int>{5, 8, 9, 14};
	case BLUE:
		return std::vector<int>{10, 13, 19, 21};
	case ORANGE:
		return std::vector<int>{11, 16, 17, 22};
	case WHITE:
		return std::vector<int>{4, 6, 7, 12};
	}

	return std::vector<int>();
}

void Rubik::initAllCornersNumbersFromColors() {
	int modulo = 8;
	for (int i1 = 0; i1 < modulo; i1++) //Iterate from corner piece 0 to corner piece 8
	{
		computeCornerPieceNumberFromColors(i1);
	}
}


void Rubik::computeCornerPieceNumberFromColors(int i1) {
	//Compute the 3 # of the corner piece (modulo 8)
	i1 = i1 % 8;
	int i2 = i1 + 8;
	int i3 = i2 + 8;

	//Find the individual possible indexes for the given colors
	std::vector<int> number1 = getPossibleCornerNumbersFromColor(this->corners[i1]->getColor());
	std::vector<int> number2 = getPossibleCornerNumbersFromColor(this->corners[i2]->getColor());
	std::vector<int> number3 = getPossibleCornerNumbersFromColor(this->corners[i3]->getColor());
	int size1 = number1.size();
	int size2 = number2.size();
	int size3 = number3.size();

	//Find the numbers that match (modulo 8)
	for (int a = 0; a < size1; a++) {
		for (int b = 0; b < size2; b++) {
			for (int c = 0; c < size3; c++) {
				if (number1[a] % 8 == number2[b] % 8 && number2[b] % 8 == number3[c] % 8) {
					this->corners[i1]->setNumber(number1[a]);
					this->corners[i2]->setNumber(number2[b]);
					this->corners[i3]->setNumber(number3[c]);
					return;
				}
			}
		}
	}
	error("error finding corner from colors");
}

std::vector<int> Rubik::getPossibleCornerNumbersFromColor(RubikColor color) {
	switch (color) {
	case RED:
		return std::vector<int>{0, 1, 2, 3};
	case GREEN:
		return std::vector<int>{8, 14, 18, 20};
	case YELLOW:
		return std::vector<int>{4, 5, 10, 19};
	case BLUE:
		return std::vector<int>{11, 13, 17, 23};
	case ORANGE:
		return std::vector<int>{12, 15, 21, 22};
	case WHITE:
		return std::vector<int>{6, 7, 9, 16};
	}
	return std::vector<int>();
}

void Rubik::addCornerColor(int i, RubikColor color) {
	this->corners[i] = new CornerFace(-1, color);
}

void Rubik::addEdgeColor(int i, RubikColor color) {
	this->edges[i] = new EdgeFace(-1, color);
}

void Rubik::addMiddleColor(int i, RubikColor color) {
	int number = -1;
	switch (color) {
	case RED:
		number = 0;	break;
	case BLUE:
		number = 4;	break;
	case ORANGE:
		number = 5;	break;
	case YELLOW:
		number = 2;	break;
	case GREEN:
		number = 3;	break;
	case WHITE:
		number = 1;	break;
	default:
		break;
	}
	this->middle[i] = new MiddleFace(number, color);
}


void Rubik::initCornersAndEdges(int pieces[]) {
	int index;
	int i = 0;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 12; x++) {
			index = Rubik::lines[y][x]; //Compute index of the given face

			//Determines if it's a corner, edge or middle and adds to the corresponding array
			if (index != -1)
			{
				if (y % 3 == 0 || y % 3 == 2)
				{
					if (x % 3 == 0 || x % 3 == 2) //Corner
					{
						addCorner(index, pieces[i]);
						i++;
					}
					else //Edge
					{
						addEdge(index, pieces[i]);
						i++;
					}

				}
				else
				{
					if (x % 3 == 0 || x % 3 == 2) //Edge
					{
						addEdge(index, pieces[i]);
						i++;
					}
					else //Middle
					{
						addMiddle(index, pieces[i]);
						i++;
					}
				}
			}
		}
	}
}

void Rubik::addCorner(int i, int number)
{
	RubikColor color;
	switch (number) {
	case 0:	case 1:	case 2:	case 3:
		color = RubikColor::RED;
		break;
	case 6:	case 7:	case 9:	case 16:
		color = RubikColor::WHITE;
		break;
	case 10: case 19: case 4: case 5:
		color = RubikColor::YELLOW;
		break;
	case 14: case 8: case 18: case 20:
		color = RubikColor::GREEN;
		break;
	case 17: case 23: case 13: case 11:
		color = RubikColor::BLUE;
		break;
	case 15: case 22: case 12: case 21:
		color = RubikColor::ORANGE;
		break;
	default:
		error("corner color");
		break;
	}
	this->corners[i] = new CornerFace(number, color);
}

void Rubik::addEdge(int i, int number)
{
	RubikColor color;
	switch (number) {
	case 0: case 1: case 2: case 3:
		color = RubikColor::RED;
		break;
	case 4: case 7: case 12: case 6:
		color = RubikColor::WHITE;
		break;
	case 14: case 9: case 5: case 8:
		color = RubikColor::YELLOW;
		break;
	case 18: case 20: case 23: case 15:
		color = RubikColor::GREEN;
		break;
	case 10: case 13: case 19: case 21:
		color = RubikColor::BLUE;
		break;
	case 11: case 16: case 17: case 22:
		color = RubikColor::ORANGE;
		break;
	default:
		error("edge color");
		break;
	}
	this->edges[i] = new EdgeFace(number, color);
}

void Rubik::addMiddle(int i, int number)
{
	RubikColor color;
	switch (number) {
	case 0:
		color = RubikColor::RED;
		break;
	case 1:
		color = RubikColor::WHITE;
		break;
	case 2:
		color = RubikColor::YELLOW;
		break;
	case 3:
		color = RubikColor::GREEN;
		break;
	case 4:
		color = RubikColor::BLUE;
		break;
	case 5:
		color = RubikColor::ORANGE;
		break;
	default:
		error("middle color");
		break;
	}
	this->middle[i] = new MiddleFace(number, color);
}



void Rubik::error(std::string error) {
	//exception
	std::cout << "ERREUR : " << error << std::endl;
}


void Rubik::setVerbose(bool value) {
	Rubik::debug = value;
}


void Rubik::printCube() {
	int number;
	int index;
	for (int y = 0; y < 9; y++) {
		std::cout << std::endl;

		for (int x = 0; x < 12; x++) {
			index = Rubik::lines[y][x];
			if (index == -1) { //Space
				std::cout << "  ";
			}
			else
			{
				if (y % 3 == 0 || y % 3 == 2)
				{
					if (x % 3 == 0 || x % 3 == 2) //Corner
					{
						number = this->corners[Rubik::lines[y][x]]->getNumber();
						if (number < 10 && number >= 0) {
							std::cout << " ";
						}
						std::cout << setcolor(this->corners[Rubik::lines[y][x]]->getColor()) << number;
					}
					else //Edge
					{
						number = this->edges[Rubik::lines[y][x]]->getNumber();
						if (number < 10 && number >= 0) {
							std::cout << " ";
						}
						std::cout << setcolor(this->edges[Rubik::lines[y][x]]->getColor()) << number;
					}

				}
				else
				{
					if (x % 3 == 0 || x % 3 == 2) //Edge
					{
						number = this->edges[Rubik::lines[y][x]]->getNumber();
						if (number < 10 && number >= 0) {
							std::cout << " ";
						}
						std::cout << setcolor(this->edges[Rubik::lines[y][x]]->getColor()) << number;
					}
					else //Middle
					{
						number = this->middle[Rubik::lines[y][x]]->getNumber();
						std::cout << " " << setcolor(this->middle[Rubik::lines[y][x]]->getColor()) << number;
					}
				}
			}

			std::cout << " ";
		}
	}
	std::cout << setcolor(RubikColor::WHITE) << std::endl; //Change the color of the terminal
}

bool Rubik::verifyRubikColors(RubikColor colors[]) {
	int rotate = 0;
	bool result = false;
	int i = 0;
	while (!result && rotate < 4) {
		if (this->corners[6]->getColor() == colors[i++] 
			&& this->edges[4]->getColor() == colors[i++] 
			&& this->corners[7]->getColor() == colors[i++]
			&& this->edges[6]->getColor() == colors[i++] 
			&& this->middle[1]->getColor() == colors[i++] 
			&& this->edges[7]->getColor() == colors[i++]
			&& this->corners[16]->getColor() == colors[i++] 
			&& this->edges[12]->getColor() == colors[i++]
			&& this->corners[9]->getColor() == colors[i++])
		{
			result = true;
		}

		//If it's not matching, turn the top layer of the cube to check if the cube is not just badly-oriented
		rotate++;
		U();
	}
	return result;
}

void Rubik::shift(Face * array[], int i1, int i2, int i3, int i4) {
	Face * temp = array[i1];
	array[i1] = array[i2];
	array[i2] = array[i3];
	array[i3] = array[i4];
	array[i4] = temp;
}

void Rubik::shift(CornerFace * array[], int i1, int i2, int i3, int i4) {
	this->shift((Face**)array, i1, i2, i3, i4);
}
void Rubik::shift(EdgeFace * array[], int i1, int i2, int i3, int i4) {
	this->shift((Face**)array, i1, i2, i3, i4);
}

void Rubik::shift(MiddleFace * array[], int i1, int i2, int i3, int i4) {
	this->shift((Face**)array, i1, i2, i3, i4);
}

void Rubik::swap(Face * array[], int i1, int i2) {
	Face * temp = array[i1];
	array[i1] = array[i2];
	array[i2] = temp;
}


void Rubik::Ri(bool isAddToMoves) {
	shift(this->corners, 9, 15, 5, 3);
	shift(this->corners, 7, 21, 19, 1);
	shift(this->corners, 17, 23, 13, 11);
	shift(this->edges, 7, 22, 9, 1);
	shift(this->edges, 19, 10, 21, 13);

	if (isAddToMoves)
		addMove(this->movesDictionary[_Ri]);
}


void Rubik::R(bool isAddToMoves) {
	shift(this->corners, 3, 5, 15, 9);
	shift(this->corners, 1, 19, 21, 7);
	shift(this->corners, 11, 13, 23, 17);
	shift(this->edges, 1, 9, 22, 7);
	shift(this->edges, 13, 21, 10, 19);

	if (isAddToMoves)
		addMove(this->movesDictionary[_R]);
}
void Rubik::R2(bool isAddToMoves) {
	swap((Face**)this->corners, 3, 15);
	swap((Face**)this->corners, 5, 9);
	swap((Face**)this->corners, 1, 21);
	swap((Face**)this->corners, 19, 7);
	swap((Face**)this->corners, 11, 23);
	swap((Face**)this->corners, 13, 17);

	swap((Face**)this->edges, 1, 22);
	swap((Face**)this->edges, 9, 7);
	swap((Face**)this->edges, 13, 10);
	swap((Face**)this->edges, 21, 19);

	if (isAddToMoves)
		addMove(this->movesDictionary[_R2]);
}
void Rubik::Li(bool isAddToMoves) {
	shift(this->corners, 16, 2, 4, 22);
	shift(this->corners, 6, 0, 10, 12);
	shift(this->corners, 8, 18, 20, 14);
	shift(this->edges, 6, 3, 8, 11);
	shift(this->edges, 18, 15, 20, 23);

	if (isAddToMoves)
		addMove(this->movesDictionary[_Li]);
}
void Rubik::L(bool isAddToMoves) {
	shift(this->corners, 22, 4, 2, 16);
	shift(this->corners, 12, 10, 0, 6);
	shift(this->corners, 14, 20, 18, 8);
	shift(this->edges, 11, 8, 3, 6);
	shift(this->edges, 23, 20, 15, 18);

	if (isAddToMoves)
		addMove(this->movesDictionary[_L]);
}

void Rubik::L2(bool isAddToMoves) {
	swap((Face**)this->corners, 22, 2);
	swap((Face**)this->corners, 4, 16);
	swap((Face**)this->corners, 12, 0);
	swap((Face**)this->corners, 10, 6);
	swap((Face**)this->corners, 14, 18);
	swap((Face**)this->corners, 20, 8);

	swap((Face**)this->edges, 11, 3);
	swap((Face**)this->edges, 8, 6);
	swap((Face**)this->edges, 23, 15);
	swap((Face**)this->edges, 20, 18);

	if (isAddToMoves)
		addMove(this->movesDictionary[_L2]);
}
void Rubik::Ui(bool isAddToMoves) {
	shift(this->corners, 9, 16, 6, 7);
	shift(this->corners, 1, 8, 22, 23);
	shift(this->corners, 0, 14, 15, 17);
	shift(this->edges, 4, 7, 12, 6);
	shift(this->edges, 0, 18, 16, 19);

	if (isAddToMoves)
		addMove(this->movesDictionary[_Ui]);
}
void Rubik::U(bool isAddToMoves) {
	shift(this->corners, 7, 6, 16, 9);
	shift(this->corners, 23, 22, 8, 1);
	shift(this->corners, 17, 15, 14, 0);
	shift(this->edges, 6, 12, 7, 4);
	shift(this->edges, 19, 16, 18, 0);

	if (isAddToMoves)
		addMove(this->movesDictionary[_U]);
}

void Rubik::U2(bool isAddToMoves) {
	swap((Face**)this->corners, 7, 16);
	swap((Face**)this->corners, 6, 9);
	swap((Face**)this->corners, 17, 14);
	swap((Face**)this->corners, 15, 0);
	swap((Face**)this->corners, 23, 8);
	swap((Face**)this->corners, 22, 1);

	swap((Face**)this->edges, 6, 7);
	swap((Face**)this->edges, 12, 4);
	swap((Face**)this->edges, 19, 18);
	swap((Face**)this->edges, 16, 0);

	if (isAddToMoves)
		addMove(this->movesDictionary[_U2]);
}
void Rubik::Bi(bool isAddToMoves) {
	shift(this->corners, 7, 14, 4, 13);
	shift(this->corners, 6, 20, 5, 23);
	shift(this->corners, 22, 12, 21, 15);
	shift(this->edges, 4, 23, 5, 10);
	shift(this->edges, 16, 11, 17, 22);

	if (isAddToMoves)
		addMove(this->movesDictionary[_Bi]);
}
void Rubik::B(bool isAddToMoves) {
	shift(this->corners, 13, 4, 14, 7);
	shift(this->corners, 23, 5, 20, 6);
	shift(this->corners, 15, 21, 12, 22);
	shift(this->edges, 10, 5, 23, 4);
	shift(this->edges, 22, 17, 11, 16);

	if (isAddToMoves)
		addMove(this->movesDictionary[_B]);
}
void Rubik::B2(bool isAddToMoves) {
	swap((Face**)this->corners, 13, 14);
	swap((Face**)this->corners, 4, 7);
	swap((Face**)this->corners, 23, 20);
	swap((Face**)this->corners, 5, 6);
	swap((Face**)this->corners, 15, 12);
	swap((Face**)this->corners, 21, 22);

	swap((Face**)this->edges, 10, 23);
	swap((Face**)this->edges, 5, 4);
	swap((Face**)this->edges, 22, 11);
	swap((Face**)this->edges, 17, 16);

	if (isAddToMoves)
		addMove(this->movesDictionary[_B2]);
}
void Rubik::Fi(bool isAddToMoves) {
	shift(this->corners, 9, 11, 10, 8);
	shift(this->corners, 16, 17, 19, 18);
	shift(this->corners, 0, 1, 3, 2);
	shift(this->edges, 12, 13, 14, 15);
	shift(this->edges, 0, 1, 2, 3);

	if (isAddToMoves)
		addMove(this->movesDictionary[_Fi]);
}
void Rubik::F(bool isAddToMoves) {
	shift(this->corners, 8, 10, 11, 9);
	shift(this->corners, 18, 19, 17, 16);
	shift(this->corners, 2, 3, 1, 0);
	shift(this->edges, 15, 14, 13, 12);
	shift(this->edges, 3, 2, 1, 0);

	if (isAddToMoves)
		addMove(this->movesDictionary[_F]);
}
void Rubik::F2(bool isAddToMoves) {
	swap((Face**)this->corners, 3, 0);
	swap((Face**)this->corners, 2, 1);
	swap((Face**)this->corners, 8, 11);
	swap((Face**)this->corners, 10, 9);
	swap((Face**)this->corners, 18, 17);
	swap((Face**)this->corners, 19, 16);

	swap((Face**)this->edges, 2, 0);
	swap((Face**)this->edges, 3, 1);
	swap((Face**)this->edges, 15, 13);
	swap((Face**)this->edges, 14, 12);

	if (isAddToMoves)
		addMove(this->movesDictionary[_F2]);
}
void Rubik::Di(bool isAddToMoves) {
	shift(this->corners, 3, 13, 12, 18);
	shift(this->corners, 2, 11, 21, 20);
	shift(this->corners, 19, 5, 4, 10);
	shift(this->edges, 2, 21, 17, 20);
	shift(this->edges, 14, 9, 5, 8);

	if (isAddToMoves)
		addMove(this->movesDictionary[_Di]);
}
void Rubik::D(bool isAddToMoves) {
	shift(this->corners, 18, 12, 13, 3);
	shift(this->corners, 20, 21, 11, 2);
	shift(this->corners, 10, 4, 5, 19);
	shift(this->edges, 20, 17, 21, 2);
	shift(this->edges, 8, 5, 9, 14);

	if (isAddToMoves)
		addMove(this->movesDictionary[_D]);
}

void Rubik::D2(bool isAddToMoves){

	swap((Face**)this->corners, 3, 12);
	swap((Face**)this->corners, 11, 20);
	swap((Face**)this->corners, 19, 4);
	swap((Face**)this->corners, 2, 21);
	swap((Face**)this->corners, 18, 13);
	swap((Face**)this->corners, 10, 5);
	swap((Face**)this->edges, 2, 17);
	swap((Face**)this->edges, 21, 20);
	swap((Face**)this->edges, 14, 5);
	swap((Face**)this->edges, 9, 8);

	if (isAddToMoves)
		addMove(this->movesDictionary[_D2]);
}

void Rubik::changeReferential(RubikColor color) {
	HumanSolver solver;
	solver.resolveMiddle(this, color);
}

void Rubik::resolve(RubikColor colors[]) {
	HumanSolver solver;
	solver.resolve(this, colors);
}

void Rubik::resolve(RubikColor colors[], Robot * pRobot) {
	RobotSolver solver(pRobot);
	solver.resolve(this, colors);
}

void Rubik::turnCubeRight() { //White to blue
	Fi(false);
	B(false);
	this->shift(this->middle, 3, 1, 4, 2);
	this->shift(this->edges, 6, 19, 9, 20);
	this->shift(this->edges, 7, 21, 8, 18);

	std::map<std::string, std::string> tempMap(movesDictionary);
	//Dictionary
	movesDictionary[_R] = tempMap[_D];
	movesDictionary[_Ri] = tempMap[_Di];
	movesDictionary[_R2] = tempMap[_D2];
	movesDictionary[_L] = tempMap[_U];
	movesDictionary[_Li] = tempMap[_Ui];
	movesDictionary[_L2] = tempMap[_U2];
	movesDictionary[_U] = tempMap[_R];
	movesDictionary[_Ui] = tempMap[_Ri];
	movesDictionary[_U2] = tempMap[_R2];
	/*movesDictionary[_B] = movesDictionary[_B];
	movesDictionary[_Bi] = movesDictionary[_Bi];
	movesDictionary[_B2] = movesDictionary[_B2];
	movesDictionary[_F] = movesDictionary[_F];
	movesDictionary[_Fi] = movesDictionary[_Fi];
	movesDictionary[_F2] = movesDictionary[_F2];*/
	movesDictionary[_D] = tempMap[_L];
	movesDictionary[_Di] = tempMap[_Li];
	movesDictionary[_D2] = tempMap[_L2];

}

void Rubik::turnCubeUp() { //White to orange
	Ri(false);
	L(false);
	this->shift(this->middle, 0, 1, 5, 2);
	this->shift(this->edges, 4, 17, 14, 0);
	this->shift(this->edges, 12, 16, 5, 2);

	std::map<std::string, std::string> tempMap(movesDictionary);
	//Dictionary
	/*movesDictionary[movesDictionary[_R]] = movesDictionary[_R];
	movesDictionary[movesDictionary[_Ri]] = movesDictionary[_Ri];
	movesDictionary[movesDictionary[_R2]] = movesDictionary[_R2];
	movesDictionary[movesDictionary[_L]] = movesDictionary[_L];
	movesDictionary[movesDictionary[_Li]] = movesDictionary[_Li];
	movesDictionary[movesDictionary[_L2]] = movesDictionary[_L2];*/
	movesDictionary[_U] = tempMap[_B];
	movesDictionary[_Ui] = tempMap[_Bi];
	movesDictionary[_U2] = tempMap[_B2];
	movesDictionary[_B] = tempMap[_D];
	movesDictionary[_Bi] = tempMap[_Di];
	movesDictionary[_B2] = tempMap[_D2];
	movesDictionary[_F] = tempMap[_U];
	movesDictionary[_Fi] = tempMap[_Ui];
	movesDictionary[_F2] = tempMap[_U2];
	movesDictionary[_D] = tempMap[_F];
	movesDictionary[_Di] = tempMap[_Fi];
	movesDictionary[_D2] = tempMap[_F2];
}

void Rubik::turnCubeDown() { //White to red
	R(false);
	Li(false);
	this->shift(this->middle, 0, 2, 5, 1);
	this->shift(this->edges, 4, 0, 14, 17);
	this->shift(this->edges, 12, 2, 5, 16);

	std::map<std::string, std::string> tempMap(movesDictionary);

	//Dictionary
	/*movesDictionary[movesDictionary[_R]] = movesDictionary[_R];
	movesDictionary[movesDictionary[_Ri]] = movesDictionary[_Ri];
	movesDictionary[movesDictionary[_R2]] = movesDictionary[_R2];
	movesDictionary[movesDictionary[_L]] = movesDictionary[_L];
	movesDictionary[movesDictionary[_Li]] = movesDictionary[_Li];
	movesDictionary[movesDictionary[_L2]] = movesDictionary[_L2];*/
	movesDictionary[_U] = tempMap[_F];
	movesDictionary[_Ui] = tempMap[_Fi];
	movesDictionary[_U2] = tempMap[_F2];
	movesDictionary[_B] = tempMap[_U];
	movesDictionary[_Bi] = tempMap[_Ui];
	movesDictionary[_B2] = tempMap[_U2];
	movesDictionary[_F] = tempMap[_D];
	movesDictionary[_Fi] = tempMap[_Di];
	movesDictionary[_F2] = tempMap[_D2];
	movesDictionary[_D] = tempMap[_B];
	movesDictionary[_Di] = tempMap[_Bi];
	movesDictionary[_D2] = tempMap[_B2];

}
void Rubik::turnCubeLeft() { //White to green
	F(false);
	Bi(false);
	this->shift(this->middle, 3, 2, 4, 1);
	this->shift(this->edges, 6, 20, 9, 19);
	this->shift(this->edges, 7, 18, 8, 21);

	std::map<std::string, std::string> tempMap(movesDictionary);
	//Dictionary

	movesDictionary[_R] = tempMap[_U];
	movesDictionary[_Ri] = tempMap[_Ui];
	movesDictionary[_R2] = tempMap[_U2];
	movesDictionary[_L] = tempMap[_D];
	movesDictionary[_Li] = tempMap[_Di];
	movesDictionary[_L2] = tempMap[_D2];
	movesDictionary[_U] = tempMap[_L];
	movesDictionary[_Ui] = tempMap[_Li];
	movesDictionary[_U2] = tempMap[_L2];
	/*movesDictionary[_B] = movesDictionary[_B];
	movesDictionary[_Bi] = movesDictionary[_Bi];
	movesDictionary[_B2] = movesDictionary[_B2];
	movesDictionary[_F] = movesDictionary[_F];
	movesDictionary[_Fi] = movesDictionary[_Fi];
	movesDictionary[_F2] = movesDictionary[_F2];*/
	movesDictionary[_D] = tempMap[_R];
	movesDictionary[_Di] = tempMap[_Ri];
	movesDictionary[_D2] = tempMap[_R2];

}

void Rubik::setLockedEdge(int index, bool value) {
	int edgeIndex = index % 12;
	this->edges[edgeIndex]->setLocked(value);
	this->edges[edgeIndex + 12]->setLocked(value);
}


void Rubik::applyMoves(std::vector<std::string>& m) {
	int size = m.size();
	for (int i = 0; i < size; i++) {
		applyMove(m[i]);
	}
}


void Rubik::applyMove(std::string m) {
	pfunc f = movesFunctions[m];
	(this->*f)(true);
}

void Rubik::setLockedCorner(int index, bool value) {
	int cornerIndex = index % 8;
	this->corners[cornerIndex]->setLocked(value);
	this->corners[cornerIndex + 8]->setLocked(value);
	this->corners[cornerIndex + 16]->setLocked(value);
}


CornerFace * Rubik::getCorner(int i) {
	if (i < 0 || i > 23) {
		return NULL;
	}
	return this->corners[i];
}


EdgeFace * Rubik::getEdge(int i) {
	if (i < 0 || i > 23) {
		return NULL;
	}
	return this->edges[i];
}


MiddleFace * Rubik::getMiddle(int i) {
	if (i < 0 || i > 7) {
		return NULL;
	}
	return this->middle[i];
}


std::string Rubik::getMoveAtIndex(int i) {
	if (i >= 0 && i < this->moves.size()) {
		return this->moves[i];
	}
	return "";
}

int Rubik::getNbMoves() {
	return this->moves.size();
}


void Rubik::optimise() {
	int size = this->moves.size();

	if (size < 2)
	{
		return;
	}

	if (Rubik::debug) {
		std::cout << "Optimising" << std::endl;
		printCube();
		std::cout << std::endl;
		for (unsigned int i = 0; i < this->moves.size(); i++) {
			std::cout << moves[i] << " ";
		}
		this->printCube();
		std::cout << "--------------------------------------------------------" << std::endl;
	}

	int index = 0;
	while (index < size - 1) {
		index = index >= 0 ? index : 0;
		index = index + 1 - shortenMoves(index);
		size = this->moves.size();
	}
}

int Rubik::shortenMoves(int i1)
{
	std::string m1 = this->moves[i1];
	int i2 = i1 + 1;
	std::string m2 = this->moves[i2];

	int size1 = m1.size();
	int size2 = m2.size();

	if (m1[0] == m2[0])
	{
		if (size1 == 1 && size2 == 1)//R R
		{
			this->moves[i1] += "2";
			this->moves.erase(this->moves.begin() + i2);
			return 1;
		}
		else if (size1 == 1 && size2 == 2)//R ; Ri ou R2
		{
			if (m2[1] == 'i')//R ; Ri
			{
				this->moves.erase(this->moves.begin() + i2);
				this->moves.erase(this->moves.begin() + i1);
				return 2;
			}
			else //R ; R2
			{
				this->moves[i1] += "i";
				this->moves.erase(this->moves.begin() + i2);
				return 1;
			}
		}
		else if (size1 == 2 && size2 == 1)//Ri ou R2; R
		{
			if (m1[1] == 'i')//Ri ; R
			{
				this->moves.erase(this->moves.begin() + i2);
				this->moves.erase(this->moves.begin() + i1);
				return 2;
			}
			else //R2 ; R
			{
				this->moves[i1][1] = 'i';
				this->moves.erase(this->moves.begin() + i2);
				return 1;
			}
		}
		else if (size1 == 2 && size2 == 2)//Ri ou R2 ; Ri ou R2
		{
			if (m1 == m2)  //Ri ; Ri ou R2 ; R2
			{
				if (m1[1] == 'i') //Ri ; Ri
				{
					this->moves[i1][1] = '2';
					this->moves.erase(this->moves.begin() + i2);
					return 1;
				}
				else //R2 ; R2
				{
					this->moves.erase(this->moves.begin() + i2);
					this->moves.erase(this->moves.begin() + i1);
					return 2;
				}
			}
			else //Ri ; R2 ou R2 ; Ri
			{
				this->moves[i1] = m1[0];
				this->moves.erase(this->moves.begin() + i2);
				return 1;
			}
		}
	}
	return 0;
}


void Rubik::addMove(std::string m2) {
	if (this->moves.size() <= 0) {
		this->moves.push_back(m2);
		return;
	}

	int i1 = this->moves.size() - 1;
	std::string m1 = this->moves[i1];

	int size1 = m1.size();
	int size2 = m2.size();

	if (m1[0] == m2[0])
	{
		if (size1 == 1 && size2 == 1)//R R
		{
			this->moves[i1] += "2";
			return;
		}
		else if (size1 == 1 && size2 == 2)//R ; Ri ou R2
		{
			if (m2[1] == 'i')//R ; Ri
			{
				this->moves.erase(this->moves.begin() + i1);
				return;
			}
			else //R ; R2
			{
				this->moves[i1] += "i";
				return;
			}
		}
		else if (size1 == 2 && size2 == 1)//Ri ou R2; R
		{
			if (m1[1] == 'i')//Ri ; R
			{
				this->moves.erase(this->moves.begin() + i1);
				return;
			}
			else //R2 ; R
			{
				this->moves[i1][1] = 'i';
				return;
			}
		}
		else if (size1 == 2 && size2 == 2)//Ri ou R2 ; Ri ou R2
		{
			if (m1 == m2)  //Ri ; Ri ou R2 ; R2
			{
				if (m1[1] == 'i') //Ri ; Ri
				{
					this->moves[i1][1] = '2';
					return;
				}
				else //R2 ; R2
				{
					this->moves.erase(this->moves.begin() + i1);
					return;
				}
			}
			else //Ri ; R2 ou R2 ; Ri
			{
				this->moves[i1] = m1[0];
				return;
			}
		}
	}

	this->moves.push_back(m2);

}

