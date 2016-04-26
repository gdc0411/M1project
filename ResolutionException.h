#ifndef RESOLUTIONEXCEPTION_HEADER

#define RESOLUTIONEXCEPTION_HEADER
#include <exception>
#include <string>
#include "RubikColor.h"

/// <summary>
/// Exception : The cube resolution is wrong
/// </summary>
/// <seealso cref="std::exception" />
class ResolutionException : public std::exception
{
public:
	/** Constructor (C strings).
	*  @param message C-style string error message.
	*                 The string contents are copied upon construction.
	*                 Hence, responsibility for deleting the \c char* lies
	*                 with the caller.
	*/
	explicit ResolutionException(const char* message, RubikColor colors[]) :
		msg_(message)
	{
		for (int i = 0; i < 9; i++)
		{
			this->colors[i] = colors[i];
		}
	}

	/** Constructor (C++ STL strings).
	*  @param message The error message.
	*/
	explicit ResolutionException(const std::string& message, RubikColor colors[]) :
		msg_(message)
	{
		for (int i = 0; i < 9; i++)
		{
			this->colors[i] = colors[i];
		}
	}

	/** Destructor.
	* Virtual to allow for subclassing.
	*/
	virtual ~ResolutionException() throw (){}

	/** Returns a pointer to the (constant) error description.
	*  @return A pointer to a \c const \c char*. The underlying memory
	*          is in posession of the \c Exception object. Callers \a must
	*          not attempt to free the memory.
	*/
	virtual const char* what() const throw (){
		return msg_.c_str();
	}

	RubikColor * getColors() {
		return this->colors;
	}

protected:
	/** Error message.
	*/
	std::string msg_;

private:
	RubikColor colors[9];
};

#endif