#ifndef CORNERFACE_HEADER

#define CORNERFACE_HEADER

#include "Face.h"

/// <summary>
/// Class representing a corner face of the cube
/// </summary>
/// <seealso cref="Face" />
class CornerFace : public Face {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="CornerFace" /> class.
	/// </summary>
	/// <param name="number">The number.</param>
	/// <param name="color">The color.</param>
	CornerFace(int number, RubikColor color);

	/// <summary>
	/// Gets the corner piece number
	/// </summary>
	/// <returns>Number % 8</returns>
	int getPieceNumber();
};

#endif