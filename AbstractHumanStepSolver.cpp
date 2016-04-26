#include "AbstractHumanStepSolver.h"
#include "Rubik.h"

void AbstractHumanStepSolver::resolve(Rubik * pRubik, RubikColor colors[]) {
	resolveMiddle(pRubik, colors[4]);
	RubikColor edgesColors[4] = { colors[7], colors[5], colors[1], colors[3] };
	RubikColor cornersColors[4] = { colors[6], colors[8], colors[2], colors[0] };
	resolveEdges(pRubik, edgesColors);
	resolveCorners(pRubik, cornersColors);
}

void AbstractHumanStepSolver::resolveMiddle(Rubik * pRubik, RubikColor color) {
	int index = this->searchMiddleColorIndex(pRubik, color);
	pRubik->getMiddle(index)->setLocked(true);
	if (Rubik::debug) pRubik->printCube();
}

void AbstractHumanStepSolver::resolveEdges(Rubik * pRubik, RubikColor colors[]) {

	int solvedEdges = 0;

	for (int i = 0; i < 4; i++) {
		RubikColor color = colors[i]; //12 7 4 6
		int index = this->searchEdgeColorIndex(pRubik, color, solvedEdges);
		if (index == -1) {
			std::cout << "did not find edge" << std::endl;
			return;
		}
		if (Rubik::debug) std::cout << "Edge : Number " << pRubik->getEdge(index)->getNumber() << " at position " << index << std::endl;

		pRubik->setLockedEdge(12, TRUE);
		solvedEdges++;
		pRubik->U();

		if (Rubik::debug) {
			std::cout << std::endl;
			std::vector<std::string> moves = pRubik->getMoves();
			int size = moves.size();
			for (unsigned int i = 0; i < size; i++) {
				std::cout << moves[i] << " ";
			}
			pRubik->printCube();
			std::cout << "--------------------------------------------------------" << std::endl;
		}

	}
}

void AbstractHumanStepSolver::resolveCorners(Rubik * pRubik, RubikColor colors[]) {
	int solvedCorners = 0;

	for (int i = 0; i < 4; i++) {
		RubikColor color = colors[i]; //16 9 7 6
		int index = this->searchCornerColorIndex(pRubik, color, solvedCorners);
		if (index == -1) {
			std::cout << "Did not find corner" << std::endl;
		}
		if (Rubik::debug) std::cout << "Corner : Number " << pRubik->getCorner(index)->getNumber() << " at position " << index << std::endl;

		pRubik->setLockedCorner(16, true);

		solvedCorners++;
		pRubik->U();

		if (Rubik::debug) {
			std::cout << std::endl;
			std::vector<std::string> moves = pRubik->getMoves();
			int size = moves.size();
			for (unsigned int i = 0; i < size; i++) {
				std::cout << moves[i] << " ";
			}
			pRubik->printCube();
			std::cout << "--------------------------------------------------------" << std::endl;
		}
	}

}


bool AbstractHumanStepSolver::checkEdgeColor(Rubik * pRubik, int index, RubikColor color) { //locked
	if (pRubik->getEdge(index)->isLocked() == false && pRubik->getEdge(index)->getColor() == color)
	{
		return true;
	}
	return false;
}




bool AbstractHumanStepSolver::checkCornerColor(Rubik * pRubik, int index, RubikColor color) { //locked
	if (pRubik->getCorner(index)->isLocked() == false && pRubik->getCorner(index)->getColor() == color)
	{
		return true;
	}
	return false;
}



int AbstractHumanStepSolver::searchMiddleColorIndex(Rubik * pRubik, RubikColor color) {
	if (checkMiddleColor(pRubik, 1, color)) {
		//No moves
		return 1;
	}

	if (checkMiddleColor(pRubik, 0, color)) {
		//Moves
		pRubik->turnCubeDown();
		if (Rubik::debug)
			std::cout << "Down" << std::endl;
		return 0;
	}

	if (checkMiddleColor(pRubik, 3, color)) {
		//Moves
		pRubik->turnCubeLeft();
		if (Rubik::debug)
			std::cout << "Left" << std::endl;
		return 3;
	}

	if (checkMiddleColor(pRubik, 4, color)) {
		//Moves
		pRubik->turnCubeRight();
		if (Rubik::debug)
			std::cout << "Right" << std::endl;
		return 4;
	}

	if (checkMiddleColor(pRubik, 5, color)) {
		//Moves
		pRubik->turnCubeUp();
		if (Rubik::debug)
			std::cout << "Up" << std::endl;
		return 5;
	}

	if (checkMiddleColor(pRubik, 2, color)) {
		//Moves
		pRubik->turnCubeDown();
		pRubik->turnCubeDown();
		if (Rubik::debug)
			std::cout << "Down^2" << std::endl;
		return 2;
	}

	return 1;
}

bool AbstractHumanStepSolver::checkMiddleColor(Rubik * pRubik, int i, RubikColor color) {
	if (pRubik->getMiddle(i)->getColor() == color)
		return true;
	return false;
}