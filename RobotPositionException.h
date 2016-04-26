#ifndef ROBOTPOSITIONEXCEPTION_H
#define	ROBOTPOSITIONEXCEPTION_H

#include <string>
#include <iostream>
#include <exception>

using std::string;
using std::exception;

/// <summary>
/// Exception : The robot doesn't make a move
/// </summary>
/// <seealso cref="exception" />
class RobotPositionException : public exception {
private:
	string msg;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="RobotPositionException"/> class.
	/// </summary>
	/// <param name="_msg">The message.</param>
	RobotPositionException(string _msg) throw()
		: msg(_msg) {
	};

	virtual const char* what() const throw()
	{
		return this->msg.c_str();
	}

	virtual ~RobotPositionException() throw()
	{};

};

#endif	/* ROBOTPOSITIONEXCEPTION_H */