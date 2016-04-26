#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define	INDEXOUTOFBOUNDSEXCEPTION_H

#include <string>
#include <iostream>
#include <exception>

using std::string;
using std::exception;


/// <summary>
/// 
/// </summary>
/// <seealso cref="exception" />
class IndexOutOfBoundsException : public exception {
private:
	int index;
	int boundIndex;
	string msg;

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IndexOutOfBoundsException"/> class.
	/// </summary>
	/// <param name="_index">The _index.</param>
	/// <param name="_indexBound">The _index bound.</param>
	/// <param name="_msg">The _MSG.</param>
	IndexOutOfBoundsException(int _index, int _indexBound, string _msg) throw()
		: index(_index), boundIndex(_indexBound), msg(_msg) {
	};

	virtual const char* what() const throw()
	{
		return this->msg.c_str();
	}

	int getIndex() const throw(){
		return this->index;
	}

	int getBound() const throw(){
		return this->boundIndex;
	}

	virtual ~IndexOutOfBoundsException() throw()
	{};

};

#endif	/* INDEXOUTOFBOUNDSEXCEPTION_H */