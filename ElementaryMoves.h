#ifndef ELEMENTARYMOVES_HEADER

#define ELEMENTARYMOVES_HEADER

#include <string>
#include <map>

using namespace std;

class ElementaryMoves {
public:
	//ElementaryMoves();
	std::map<int, std::string> cornerMoves[4];
	std::map<int, std::string> edgeMoves[4];

}





#endif