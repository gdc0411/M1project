#include "HumanSolver.h"
#include "Rubik.h"

int HumanSolver::searchEdgeColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges) {

	if (checkEdgeColor(pRubik, 12, color)) { //0
		//No moves
		return 12;
	}

	if (checkEdgeColor(pRubik, 13, color)) { //1
		pRubik->Fi();
		return 13;
	}

	if (checkEdgeColor(pRubik, 15, color)) { //1
		pRubik->F();
		return 15;
	}

	if (checkEdgeColor(pRubik, 6, color) && solvedEdges == 0) { //1
		pRubik->Ui();
		return 6;
	}

	if (checkEdgeColor(pRubik, 7, color) && solvedEdges == 0) { //1
		pRubik->U();
		return 7;
	}

	if (checkEdgeColor(pRubik, 14, color)) { //1.5
		pRubik->F2();
		return 14;
	}

	if (checkEdgeColor(pRubik, 4, color) && solvedEdges == 0) { //1.5
		pRubik->U2();
		return 4;
	}

	if (checkEdgeColor(pRubik, 21, color) && !pRubik->getEdge(7)->isLocked()) { //2
		pRubik->R(); pRubik->Fi();
		return 21;
	}

	if (checkEdgeColor(pRubik, 20, color) && !pRubik->getEdge(6)->isLocked()) { //2
		pRubik->Li(); pRubik->F();
		return 20;
	}

	if (checkEdgeColor(pRubik, 3, color) && solvedEdges == 0) { //2
		pRubik->Li(); pRubik->Ui();
		return 3;
	}

	if (checkEdgeColor(pRubik, 11, color) && solvedEdges == 0) { //2
		pRubik->L(); pRubik->Ui();
		return 11;
	}

	if (checkEdgeColor(pRubik, 1, color) && solvedEdges == 0) { //2
		pRubik->R(); pRubik->U();
		return 1;
	}

	if (checkEdgeColor(pRubik, 22, color) && solvedEdges == 0) { //2
		pRubik->Ri(); pRubik->U();
		return 22;
	}

	if (checkEdgeColor(pRubik, 18, color)) { //2
		pRubik->L(); pRubik->F();
		return 18;
	}

	if (checkEdgeColor(pRubik, 19, color)) { //2
		pRubik->Ri(); pRubik->Fi();
		return 19;
	}

	//2.5

	if (checkEdgeColor(pRubik, 9, color)) { //2.5
		pRubik->Di(); pRubik->F2();
		return 9;
	}

	if (checkEdgeColor(pRubik, 10, color) && !pRubik->getEdge(7)->isLocked()) { //2.5
		pRubik->R2(); pRubik->Fi();
		return 10;
	}

	if (checkEdgeColor(pRubik, 23, color) && !pRubik->getEdge(6)->isLocked()) { //2.5
		pRubik->L2(); pRubik->F();
		return 23;
	}

	if (checkEdgeColor(pRubik, 8, color)) { //2.5
		pRubik->D(); pRubik->F2();
		return 8;
	}

	//2.8

	if (checkEdgeColor(pRubik, 5, color)) { //2.8
		pRubik->D2(); pRubik->F2();
		return 5;
	}

	//3

	if (checkEdgeColor(pRubik, 21, color)) { //3 //7 is locked
		pRubik->R(); pRubik->Fi(); pRubik->Ri();
		return 21;
	}

	if (checkEdgeColor(pRubik, 20, color)) { //3 //6 is locked
		pRubik->Li(); pRubik->F(); pRubik->L();
		return 20;
	}

	if (checkEdgeColor(pRubik, 3, color)) { //3
		pRubik->U(); pRubik->Li(); pRubik->Ui();
		return 3;
	}

	if (checkEdgeColor(pRubik, 11, color)) { //3
		pRubik->U(); pRubik->L(); pRubik->Ui();
		return 11;
	}

	if (checkEdgeColor(pRubik, 1, color)) { //3
		pRubik->Ui(); pRubik->R(); pRubik->U();
		return 1;
	}

	if (checkEdgeColor(pRubik, 22, color)) { //3
		pRubik->Ui();  pRubik->Ri(); pRubik->U();
		return 22;
	}

	if (checkEdgeColor(pRubik, 2, color) && !pRubik->getEdge(7)->isLocked()) { //3
		pRubik->D(); pRubik->R(); pRubik->Fi();
		return 2;
	}

	if (checkEdgeColor(pRubik, 17, color) && !pRubik->getEdge(6)->isLocked()) { //3
		pRubik->D(); pRubik->Li(); pRubik->F();
		return 17;
	}

	if (checkEdgeColor(pRubik, 10, color)) { //3.8
		pRubik->R2(); pRubik->Fi(); pRubik->R2();
		return 10;
	}

	if (checkEdgeColor(pRubik, 23, color)) { //3.8
		pRubik->L2(); pRubik->F(); pRubik->L2();
		return 23;
	}

	if (checkEdgeColor(pRubik, 2, color)) { //4
		pRubik->D(); pRubik->R(); pRubik->Fi(); pRubik->Ri();
		return 2;
	}

	if (checkEdgeColor(pRubik, 17, color)) { //4
		pRubik->D(); pRubik->Li(); pRubik->F(); pRubik->L();
		return 17;
	}

	if (checkEdgeColor(pRubik, 0, color) && !pRubik->getEdge(7)->isLocked()) //4.5
	{
		pRubik->F2(); pRubik->D(); pRubik->R(); pRubik->Fi();
		return 0;
	}

	if (checkEdgeColor(pRubik, 16, color) && !pRubik->getEdge(16)->isLocked()) { //4.5
		pRubik->B2(); pRubik->Di(); pRubik->R(); pRubik->Fi();
		return 16;
	}

	if (checkEdgeColor(pRubik, 0, color)) { //5.5
		pRubik->F2(); pRubik->D(); pRubik->R(); pRubik->Fi(); pRubik->Ri();
		return 0;
	}

	if (checkEdgeColor(pRubik, 16, color)) { //5.5
		pRubik->B2(); pRubik->Di(); pRubik->R(); pRubik->Fi(); pRubik->Ri();
		return 16;
	}

	// 6

	if (checkEdgeColor(pRubik, 4, color)) { //7
		//Don't move top !
		pRubik->Ri(); pRubik->L(); pRubik->Bi(); pRubik->R(); pRubik->Li(); pRubik->R(); pRubik->Fi();
		return 4;
	}

	if (checkEdgeColor(pRubik, 6, color)) { //9
		//Don't move top !
		pRubik->F(); pRubik->Bi(); pRubik->L(); pRubik->Fi(); pRubik->B(); pRubik->D(); pRubik->R(); pRubik->Fi(); pRubik->Ri();
		return 6;
	}

	if (checkEdgeColor(pRubik, 7, color)) { //9
		//Don't move top !
		pRubik->Fi(); pRubik->B(); pRubik->Ri(); pRubik->F(); pRubik->Bi(); pRubik->D(); pRubik->R(); pRubik->Fi(); pRubik->Ri();
		return 7;
	}
	return -1;
}



int HumanSolver::searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedCorners) {

	if (checkCornerColor(pRubik, 16, color)) { //0
		//No moves
		return 16;
	}

	if (checkCornerColor(pRubik, 11, color)) { //3
		pRubik->L(); pRubik->Di(); pRubik->Li();
		return 11;
	}

	if (checkCornerColor(pRubik, 12, color)) { //3
		pRubik->Fi(); pRubik->D(); pRubik->F();
		return 12;
	}

	if (checkCornerColor(pRubik, 11, color)) { //3
		pRubik->L(); pRubik->Di(); pRubik->Li();
		return 11;
	}

	if (checkCornerColor(pRubik, 12, color)) { //3
		pRubik->Fi(); pRubik->D(); pRubik->F();
		return 12;
	}

	if (checkCornerColor(pRubik, 2, color)) { //4
		pRubik->D(); pRubik->L(); pRubik->Di(); pRubik->Li();
		return 2;
	}

	if (checkCornerColor(pRubik, 13, color)) { //4
		pRubik->D(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 13;
	}

	if (checkCornerColor(pRubik, 18, color)) { //4
		pRubik->Di(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 18;
	}

	if (checkCornerColor(pRubik, 21, color)) { //4
		pRubik->Di(); pRubik->L(); pRubik->Di(); pRubik->Li();
		return 21;
	}

	if (checkCornerColor(pRubik, 20, color)) { //4.5
		pRubik->D2(); pRubik->L(); pRubik->Di();  pRubik->Li();
		return 20;
	}

	if (checkCornerColor(pRubik, 3, color))  { //4.5
		pRubik->D2(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 3;
	}

	if (checkCornerColor(pRubik, 17, color)) { //5
		pRubik->Ri(); pRubik->L(); pRubik->Di(); pRubik->Li(); pRubik->R();
		return 17;

	}

	if (checkCornerColor(pRubik, 22, color)) { //5
		pRubik->B(); pRubik->Fi(); pRubik->D(); pRubik->Bi(); pRubik->F();
		return 22;
	}

	if (checkCornerColor(pRubik, 1, color)) { //5.8
		pRubik->F(); pRubik->D2(); pRubik->F2(); pRubik->D(); pRubik->F();
		return 1;
	}


	if (checkCornerColor(pRubik, 14, color)) { //5.8
		pRubik->Li(); pRubik->D2(); pRubik->L2(); pRubik->Di(); pRubik->Li();
		return 14;
	}

	if (checkCornerColor(pRubik, 7, color)) { //6
		pRubik->Bi(); pRubik->D(); pRubik->Fi(); pRubik->D(); pRubik->F(); pRubik->B();
		return 7;
	}

	if (checkCornerColor(pRubik, 15, color)) { //6
		pRubik->Bi(); pRubik->Di(); pRubik->B(); pRubik->L(); pRubik->Di(); pRubik->Li();
		return 15;
	}

	if (checkCornerColor(pRubik, 23, color)) { //6
		pRubik->R(); pRubik->D(); pRubik->Fi(); pRubik->D(); pRubik->F(); pRubik->Ri();
		return 23;

	}

	if (checkCornerColor(pRubik, 6, color)) { //6.5
		pRubik->B(); pRubik->D2(); pRubik->Bi(); pRubik->L(); pRubik->Di(); pRubik->Li();
		return 6;

	}

	if (checkCornerColor(pRubik, 0, color)) { //7.5
		pRubik->Fi(); pRubik->Di(); pRubik->F(); pRubik->D2(); pRubik->L(); pRubik->Di(); pRubik->Li();
		return 0;
	}

	if (checkCornerColor(pRubik, 8, color)) { //7.5
		pRubik->L(); pRubik->D(); pRubik->Li(); pRubik->D2(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 8;

	}

	if (checkCornerColor(pRubik, 9, color)) { //7.5
		pRubik->Ri(); pRubik->Di(); pRubik->R(); pRubik->Di(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 9;
	}

	if (checkCornerColor(pRubik, 4, color)) { //10.5 //mm combinaison pour 5, 10, 19
		pRubik->Fi(); pRubik->D(); pRubik->F(); pRubik->L(); pRubik->D(); pRubik->Li(); pRubik->D2(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 4;
	}

	if (checkCornerColor(pRubik, 5, color)) { //11.5
		pRubik->D(); pRubik->Fi(); pRubik->D(); pRubik->F(); pRubik->L(); pRubik->D(); pRubik->Li(); pRubik->D2(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 5;
	}

	if (checkCornerColor(pRubik, 10, color)) { //11.5
		pRubik->Di(); pRubik->Fi(); pRubik->D(); pRubik->F(); pRubik->L(); pRubik->D(); pRubik->Li(); pRubik->D2(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 10;
	}

	if (checkCornerColor(pRubik, 19, color)) { //11.8
		pRubik->D2(); pRubik->Fi(); pRubik->D(); pRubik->F(); pRubik->L(); pRubik->D(); pRubik->Li(); pRubik->D2(); pRubik->Fi(); pRubik->D(); pRubik->F();
		return 19;
	}

	return -1;

}

