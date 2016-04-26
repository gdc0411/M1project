#ifndef ABSTRACTSOLVER_H

#define ABSTRACTSOLVER_H

#include "RubikColor.h"
#include "Face.h"

class Rubik;

/// <summary>
/// Abstract solver : From a given <c>Rubik</c> instance, make moves to get to a final state
/// </summary>
class AbstractSolver {
public:	
	/// <summary>
	/// Resolves the specified p rubik.
	/// </summary>
	/// <param name="pRubik">The p rubik.</param>
	/// <param name="colors">The colors.</param>
	virtual void resolve(Rubik * pRubik, RubikColor colors[]) = 0;
};

#endif