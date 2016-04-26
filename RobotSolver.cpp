#include "RobotSolver.h"
#include "Rubik.h"

RobotSolver::RobotSolver(Robot * pRobot) {
	this->pRobot = pRobot;
}


bool RobotSolver::getMinCost(Rubik * pRubik, std::vector<std::string>& tempMoves, int& minCost) {
	int cost;
	if (pRubik->getMoves().size() == 0) {
		cost = pRobot->getRubikMovesCost(tempMoves, "");
	}
	else {
		cost = pRobot->getRubikMovesCost(tempMoves, pRubik->getMoveAtIndex(pRubik->getNbMoves() - 1));
	}
	if (minCost == -1) {
		minCost = cost;
		return true;
	}
	return false;
}

int RobotSolver::searchEdgeColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges) {
		int result = -1;
		int minCost = -1;
		std::vector<std::string> tempMoves;
		std::vector<std::string> resultMoves;

		if (checkEdgeColor(pRubik, 12, color)) { //0
			//No moves
			result = 12;
			minCost = 0;
		}

		if (checkEdgeColor(pRubik, 13, color)) { //1
			tempMoves.clear();
			tempMoves.push_back(_Fi);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 13;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 15, color)) { //1
			tempMoves.clear();
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 15;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 6, color) && solvedEdges == 0) { //1
			tempMoves.clear();
			tempMoves.push_back(_Ui);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 6;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 7, color) && solvedEdges == 0) { //1
			tempMoves.clear();
			tempMoves.push_back(_U);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 7;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 14, color)) { //1.5
			tempMoves.clear();
			tempMoves.push_back(_F2);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 14;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 4, color) && solvedEdges == 0) { //1.5
			tempMoves.clear();
			tempMoves.push_back(_U2);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 4;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 21, color) && !pRubik->getEdge(7)->isLocked()) { //2
			tempMoves.clear();
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 21;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 20, color) && !pRubik->getEdge(6)->isLocked()) { //2
			tempMoves.clear();
			tempMoves.push_back(_Li);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 20;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 3, color) && solvedEdges == 0) { //2
			tempMoves.clear();
			tempMoves.push_back(_Li);
			tempMoves.push_back(_Ui);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 3;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 11, color) && solvedEdges == 0) { //2
			tempMoves.clear();
			tempMoves.push_back(_L);
			tempMoves.push_back(_Ui);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 11;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 1, color) && solvedEdges == 0) { //2
			tempMoves.clear();
			tempMoves.push_back(_R);
			tempMoves.push_back(_U);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 1;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 22, color) && solvedEdges == 0) { //2
			tempMoves.clear();
			tempMoves.push_back(_Ri);
			tempMoves.push_back(_U);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 22;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 18, color)) { //2
			tempMoves.clear();
			tempMoves.push_back(_L);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 18;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 19, color)) { //2
			tempMoves.clear();
			tempMoves.push_back(_Ri);
			tempMoves.push_back(_Fi);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 19;
				resultMoves = tempMoves;
			}
		}

		//2.5

		if (checkEdgeColor(pRubik, 9, color)) { //2.5
			tempMoves.clear();
			tempMoves.push_back(_Di);
			tempMoves.push_back(_F2);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 9;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 10, color) && !pRubik->getEdge(7)->isLocked()) { //2.5
			tempMoves.clear();
			tempMoves.push_back(_R2);
			tempMoves.push_back(_Fi);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 10;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 23, color) && !pRubik->getEdge(6)->isLocked()) { //2.5
			tempMoves.clear();
			tempMoves.push_back(_L2);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 23;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 8, color)) { //2.5
			tempMoves.clear();
			tempMoves.push_back(_D);
			tempMoves.push_back(_F2);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 8;
				resultMoves = tempMoves;
			}
		}

		//2.8

		if (checkEdgeColor(pRubik, 5, color)) { //2.8
			tempMoves.clear();
			tempMoves.push_back(_D2);
			tempMoves.push_back(_F2);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 5;
				resultMoves = tempMoves;
			}
		}

		//3

		if (checkEdgeColor(pRubik, 21, color)) { //3 //7 is locked
			tempMoves.clear();
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 21;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 20, color)) { //3 //6 is locked
			tempMoves.clear();
			tempMoves.push_back(_Li);
			tempMoves.push_back(_F);
			tempMoves.push_back(_L);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 20;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 3, color)) { //3
			tempMoves.clear();
			tempMoves.push_back(_U);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_Ui);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 3;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 11, color)) { //3
			tempMoves.clear();
			tempMoves.push_back(_U);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Ui);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 11;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 1, color)) { //3
			tempMoves.clear();
			tempMoves.push_back(_Ui);
			tempMoves.push_back(_R);
			tempMoves.push_back(_U);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 1;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 22, color)) { //3
			tempMoves.clear();
			tempMoves.push_back(_Ui);
			tempMoves.push_back(_Ri);
			tempMoves.push_back(_U);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 22;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 2, color) && !pRubik->getEdge(7)->isLocked()) { //3
			tempMoves.clear();
			tempMoves.push_back(_D);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 2;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 17, color) && !pRubik->getEdge(6)->isLocked()) { //3
			tempMoves.clear();
			tempMoves.push_back(_D);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 17;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 10, color)) { //3.8
			tempMoves.clear();
			tempMoves.push_back(_R2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_R2);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 10;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 23, color)) { //3.8
			tempMoves.clear();
			tempMoves.push_back(_L2);
			tempMoves.push_back(_F);
			tempMoves.push_back(_L2);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 23;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 2, color)) { //4
			tempMoves.clear();
			tempMoves.push_back(_D);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 2;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 17, color)) { //4
			tempMoves.clear();
			tempMoves.push_back(_D);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_F);
			tempMoves.push_back(_L);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 17;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 0, color) && !pRubik->getEdge(7)->isLocked()) //4.5
		{
			tempMoves.clear();
			tempMoves.push_back(_F2);
			tempMoves.push_back(_D);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 0;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 16, color) && !pRubik->getEdge(16)->isLocked()) { //4.5
			tempMoves.clear();
			tempMoves.push_back(_B2);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 16;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 0, color)) { //5.5
			tempMoves.clear();
			tempMoves.push_back(_F2);
			tempMoves.push_back(_D);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 0;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 16, color)) { //5.5
			tempMoves.clear();
			tempMoves.push_back(_B2);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 16;
				resultMoves = tempMoves;
			}
		}

		// 6

		if (checkEdgeColor(pRubik, 4, color)) { //7
			tempMoves.clear();
			tempMoves.push_back(_Ri);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Bi);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 4;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 6, color)) { //9
			tempMoves.clear();
			tempMoves.push_back(_F);
			tempMoves.push_back(_Bi);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_B);
			tempMoves.push_back(_D);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 6;
				resultMoves = tempMoves;
			}
		}

		if (checkEdgeColor(pRubik, 7, color)) { //9
			tempMoves.clear();
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_B);
			tempMoves.push_back(_Ri);
			tempMoves.push_back(_F);
			tempMoves.push_back(_Bi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 7;
				resultMoves = tempMoves;
			}
		}

		//Apply result moves
		for (int i = 0; i < resultMoves.size(); i++) {
			pRubik->applyMove(resultMoves[i]);
		}

		return result;
	}

int RobotSolver::searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedCorners) {
		int result = -1;
		int minCost = -1;
		std::vector<std::string> tempMoves;
		std::vector<std::string> resultMoves;

		if (checkCornerColor(pRubik, 16, color)) { //0
			result = 16;
			minCost = 0;
		}

		if (checkCornerColor(pRubik, 11, color)) { //3
			tempMoves.clear();
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 11;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 12, color)) { //3
			tempMoves.clear();
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 12;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 2, color)) { //4
			tempMoves.clear();
			tempMoves.push_back(_D);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 2;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 13, color)) { //4
			tempMoves.clear();
			tempMoves.push_back(_D);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 13;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 18, color)) { //4
			tempMoves.clear();
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 18;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 21, color)) { //4
			tempMoves.clear();
			tempMoves.push_back(_Di);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 21;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 20, color)) { //4.5
			tempMoves.clear();
			tempMoves.push_back(_D2);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 20;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 3, color))  { //4.5
			tempMoves.clear();
			tempMoves.push_back(_D2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 3;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 17, color)) { //5
			tempMoves.clear();
			tempMoves.push_back(_Ri);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_R);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 17;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 22, color)) { //5
			tempMoves.clear();
			tempMoves.push_back(_B);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Bi);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 22;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 1, color)) { //5.8
			tempMoves.clear();

			tempMoves.push_back(_F);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_F2);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 1;
				resultMoves = tempMoves;
			}
		}


		if (checkCornerColor(pRubik, 14, color)) { //5.8
			tempMoves.clear();

			tempMoves.push_back(_Li);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_L2);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 14;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 7, color)) { //6
			tempMoves.clear();

			tempMoves.push_back(_Bi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			tempMoves.push_back(_B);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 7;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 15, color)) { //6
			tempMoves.clear();

			tempMoves.push_back(_Bi);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_B);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 15;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 23, color)) { //6
			tempMoves.clear();

			tempMoves.push_back(_R);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			tempMoves.push_back(_Ri);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 23;
				resultMoves = tempMoves;
			}

		}

		if (checkCornerColor(pRubik, 6, color)) { //6.5
			tempMoves.clear();

			tempMoves.push_back(_B);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_Bi);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 6;
				resultMoves = tempMoves;
			}

		}

		if (checkCornerColor(pRubik, 0, color)) { //7.5
			tempMoves.clear();

			tempMoves.push_back(_Fi);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_F);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_L);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Li);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 0;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 8, color)) { //7.5
			tempMoves.clear();

			tempMoves.push_back(_L);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 8;
				resultMoves = tempMoves;
			}

		}

		if (checkCornerColor(pRubik, 9, color)) { //7.5
			tempMoves.clear();

			tempMoves.push_back(_Ri);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_R);
			tempMoves.push_back(_Di);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 9;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 4, color)) { //10.5 //mm combinaison pour 5, 10, 19
			tempMoves.clear();

			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			tempMoves.push_back(_L);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 4;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 5, color)) { //11.5
			tempMoves.clear();

			tempMoves.push_back(_D);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			tempMoves.push_back(_L);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 5;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 10, color)) { //11.5
			tempMoves.clear();

			tempMoves.push_back(_Di);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			tempMoves.push_back(_L);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 10;
				resultMoves = tempMoves;
			}
		}

		if (checkCornerColor(pRubik, 19, color)) { //11.8
			tempMoves.clear();

			tempMoves.push_back(_D2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			tempMoves.push_back(_L);
			tempMoves.push_back(_D);
			tempMoves.push_back(_Li);
			tempMoves.push_back(_D2);
			tempMoves.push_back(_Fi);
			tempMoves.push_back(_D);
			tempMoves.push_back(_F);
			if (getMinCost(pRubik, tempMoves, minCost)) {
				result = 19;
				resultMoves = tempMoves;
			}
		}


		//Apply result moves
		for (int i = 0; i < resultMoves.size(); i++) {
			pRubik->applyMove(resultMoves[i]);
		}

		return result;

	}