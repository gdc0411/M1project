#ifndef HUMANSOLVER_H

#define HUMANSOLVER_H

#include "AbstractHumanStepSolver.h"

/// <summary>
/// Solves the cube considering human moves cost
/// </summary>
/// <seealso cref="AbstractHumanStepSolver" />
class HumanSolver : public AbstractHumanStepSolver {
protected:
	/// <summary>
	/// Searches the index of the edge color to use as a solution
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="color">The color.</param>
	/// <param name="solvedEdges">The solved edges.</param>
	/// <returns></returns>
	int searchEdgeColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges);
	/// <summary>
	/// Searches the index of the corner color to use as a solution
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="color">The color.</param>
	/// <param name="solvedCorners">The solved corners.</param>
	/// <returns></returns>
	int searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedCorners);
	
};

#endif