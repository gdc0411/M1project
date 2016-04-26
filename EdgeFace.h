
#ifndef EDGEFACE_HEADER

#define EDGEFACE_HEADER

#include "Face.h"

/// <summary>
/// Class representing an edge face of the cube
/// </summary>
/// <seealso cref="Face" />
class EdgeFace : public Face {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="EdgeFace" /> class.
	/// </summary>
	/// <param name="number">The number.</param>
	/// <param name="color">The color.</param>
	EdgeFace(int number, RubikColor color);

	/// <summary>
	/// Gets the piece number.
	/// </summary>
	/// <returns>Number % 12</returns>
	int getPieceNumber();
};

#endif