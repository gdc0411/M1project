#ifndef ROBOTSOLVER_H

#define ROBOTSOLVER_H

#include "AbstractHumanStepSolver.h"
#include <vector>
#include "Robot.h"

/// <summary>
/// Rubik's cube solver that considering the cost of the robot moves (and not the cost of human moves)
/// </summary>
/// <seealso cref="AbstractHumanStepSolver" />
class RobotSolver : public AbstractHumanStepSolver {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="RobotSolver"/> class.
	/// </summary>
	/// <param name="pRobot">The robot.</param>
	RobotSolver(Robot * pRobot);
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
	/// <param name="solvedEdges">The solved edges.</param>
	/// <returns></returns>
	int searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges);
private:
	Robot * pRobot;
	/// <summary>
	/// Computes the cost of the rubik moves
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="rubikMoves">The rubik moves.</param>
	/// <param name="minCost">The minimum cost (the value is modified)</param>
	/// <returns><c>true</c> if the <c>rubikMoves</c> is cheaper than previous <c>minCost</c>. The <c>minCost</c> is updated with the new value.</returns>
	bool getMinCost(Rubik * pRubik, std::vector<std::string>& rubikMoves, int& minCost);
};

#endif