#ifndef HUMANSTEPSOLVER_H

#define HUMANSTEPSOLVER_H

#include "AbstractSolver.h"

/// <summary>
/// Rubik solver that first solves the middle, then the cross (edges) and then the corners
/// </summary>
/// <seealso cref="AbstractSolver" />
class AbstractHumanStepSolver : public AbstractSolver {
public:
	
	/// <summary>
	/// Resolves the specified p rubik.
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="colors">The colors.</param>
	virtual void resolve(Rubik * pRubik, RubikColor colors[]);
	
	/// <summary>
	/// Resolves the middle: changes the referential to determine the cube top layer
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="colors">The colors.</param>
	virtual void resolveMiddle(Rubik * pRubik, RubikColor colors);
	
	/// <summary>
	/// Resolves the edges (the cross)
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="colors">The colors.</param>
	virtual void resolveEdges(Rubik * pRubik, RubikColor colors[]);
	
	/// <summary>
	/// Resolves the corners.
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="colors">The colors.</param>
	virtual void resolveCorners(Rubik * pRubik, RubikColor colors[]);
protected:	
	/// <summary>
	/// Checks the color of the corner.
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="index">The index.</param>
	/// <param name="color">The color.</param>
	/// <returns></returns>
	bool checkCornerColor(Rubik * pRubik, int index, RubikColor color);
	
	/// <summary>
	/// Checks the color of the edge.
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="index">The index.</param>
	/// <param name="color">The color.</param>
	/// <returns></returns>
	bool checkEdgeColor(Rubik * pRubik, int index, RubikColor color);

	/// <summary>
	/// Searches the index of the edge with the given color which is the easiest to use as solution
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="color">The color.</param>
	/// <param name="solvedEdges">The number of already solved edges (Some solutions are easier but need other edges to be removed)</param>
	/// <returns>The used index</returns>
	virtual int searchEdgeColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges) = 0;

	/// <summary>
	/// Searches the index of the corner with the given color which is the easiest to use as solution
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="color">The color.</param>
	/// <param name="solvedCorners">The solved corners.</param>
	/// <returns>
	/// The used index
	/// </returns>
	virtual int searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedCorners) = 0;
private:
	
	/// <summary>
	/// Searches the index of the middle color to put on the top layer
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="color">The color.</param>
	/// <returns></returns>
	virtual int searchMiddleColorIndex(Rubik * pRubik, RubikColor color);
	
	/// <summary>
	/// Checks the color of the middle. at index <c>index</c>
	/// </summary>
	/// <param name="pRubik">The rubik</param>
	/// <param name="index">The position of the middle piece</param>
	/// <param name="color">The color</param>
	/// <returns></returns>
	virtual bool checkMiddleColor(Rubik*, int index, RubikColor);
};

#endif