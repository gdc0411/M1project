#ifndef FACE_HEADER

#define FACE_HEADER

#include "RubikColor.h"

#define _R "R"
#define _Ri "Ri"
#define _R2 "R2"
#define _L "L"
#define _Li "Li"
#define _L2 "L2"
#define _U "U"
#define _Ui "Ui"
#define _U2 "U2"
#define _B "B"
#define _Bi "Bi"
#define _B2 "B2"
#define _F "F"
#define _Fi "Fi"
#define _F2 "F2"
#define _D "D"
#define _Di "Di"
#define _D2 "D2"

/// <summary>
/// Class representing a face of the cube
/// </summary>
class Face {
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="Face" /> class.
		/// </summary>
		/// <param name="number">The number of the piece (This is NOT the position on the cube)</param>
		/// <param name="color">The color of the piece</param>
		Face(int number, RubikColor color);

		/// <summary>
		/// Gets the number.
		/// </summary>
		/// <returns></returns>
		int getNumber() { return number; }

		/// <summary>
		/// Sets the number.
		/// </summary>
		/// <param name="">The .</param>
		void setNumber(int);

		/// <summary>
		/// Determines whether this piece is locked.
		/// </summary>
		/// <returns></returns>
		bool isLocked() { return isLockedPosition; }

		/// <summary>
		/// Locks or unlocks the piece
		/// </summary>
		/// <param name="value">if set to <c>true</c>, locks the piece.</param>
		void setLocked(bool value);

		/// <summary>
		/// Gets the color.
		/// </summary>
		/// <returns></returns>
		RubikColor getColor() { return color; }
	protected:
		bool isLockedPosition = false;
		int number;
		RubikColor color;
};

#endif