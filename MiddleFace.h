#ifndef MIDDLEFACE_HEADER

#define MIDDLEFACE_HEADER

#include "Face.h"

/// <summary>
/// Class representing a middle piece of the cube
/// </summary>
/// <seealso cref="Face" />
class MiddleFace : public Face {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="MiddleFace"/> class.
	/// </summary>
	/// <param name="">The .</param>
	/// <param name="">The .</param>
	MiddleFace(int, RubikColor);
};

#endif