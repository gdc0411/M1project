
#ifndef RUBIK_HEADER

#define RUBIK_HEADER

#include "Face.h"
#include "CornerFace.h"
#include "EdgeFace.h"
#include "MiddleFace.h"
#include "Robot.h"
#include "RobotState.h"
#include "RubikColor.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "HumanSolver.h"
#include "RobotSolver.h"

typedef void(Rubik::*pfunc)(bool);

struct Offset {
	int x;
	int y;
};

/// <summary>
/// Class representing a Rubik's cube
/// </summary>
class Rubik {
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="Rubik"/> class from an array representing the colors of the cube. 
		/// This constructor can be used after scanning the Rubik's cube with OpenCV and the robot.
		/// </summary>
		/// <param name="">an array representing the colors of the cube in this order (the scanning order of the cube with the robot): 
		///					[		Cell 0		]
		/// [	Cell 1		][		Cell 2		][		Cell 3		][		Cell 4		]
		///					[		Cell 5		].	
		/// In each cell is a vector of size 9 giving the colors of the pieces in this order :
		///	[0	1	2
		///  3	4	5
		///	 6	7	8]
		///  (first row, second row, third row)</param>
		Rubik(std::vector<std::vector<int>>&);


		/// <summary>
		/// Initializes a new instance of the <see cref="Rubik"/> class from an array giving the # of each piece
		/// </summary>
		/// <param name="">The array representing the # of each piece in the following order :
		///									[Top Layer, Row 1] 0, 1, 2 
		///									[Top Layer, Row 2] 3, 4, 5 
		///									[Top Layer, Row 3] 6, 7, 8 
		///[Left Layer, Row 1] 9, 10, 11	[Front Layer, Row 1] 12, 13, 14		[Right Layer, Row 1] 15, 16, 17		[Back Layer, Row 1] 18, 19, 20
		///[Left Layer, Row 2] 21, 22, 23	[Front Layer, Row 2] 24, 25, 26		[Right Layer, Row 2] 27, 28, 29		[Back Layer, Row 2] 30, 31, 32
		///[Left Layer, Row 3] 33, 34, 35	[Front Layer, Row 3] 36, 37, 38		[Right Layer, Row 3] 39, 40, 41		[Back Layer, Row 3] 42, 43, 44
		///									[Bottom Layer, Row 1] 45, 46, 47
		///									[Bottom Layer, Row 2] 48, 49, 50
		///									[Bottom Layer, Row 3]51, 52, 53
		///</param>
		Rubik(int[]);

		/// <summary>
		/// Finalizes an instance of the <see cref="Rubik"/> class.
		/// </summary>
		~Rubik();

		/// <summary>
		/// Prints the cube in the console with colors and the # of each piece
		/// However, orange is represented as a different color (pink= because it is not a standard color in a terminal
		/// </summary>
		void printCube();

		static bool Rubik::debug;
		/// <summary>
		/// Enables or disables the console prints when resolving the cube
		/// </summary>
		/// <param name="value">if set to <c>true</c>, prints the resolving steps in the console</param>
		static void setVerbose(bool value);

		/// <summary>
		/// Verifies the rubik colors.
		/// </summary>
		/// <param name="colors">The expected colors in the following order :
		/// [Top Layer, Row 1] 0, 1, 2
		/// [Top Layer, Row 2] 3, 4, 5
		/// [Top Layer, Row 3] 6, 7, 8
		///</param>
		/// <returns></returns>
		bool verifyRubikColors(RubikColor colors[]);

		/// <summary>
		/// Turns the right layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void R(bool isAddToMoves = true);

		/// <summary>
		/// Turns the right layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Ri(bool isAddToMoves = true);

		/// <summary>
		/// Turns the right layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void R2(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the left layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void L(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the left layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Li(bool isAddToMoves = true);

		/// <summary>
		///Turns the left layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void L2(bool isAddToMoves = true);

		/// <summary>
		/// Turns the top layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void U(bool isAddToMoves = true);

		/// <summary>
		/// Turns the top layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Ui(bool isAddToMoves = true);

		/// <summary>
		/// Turns the top layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void U2(bool isAddToMoves = true);

		/// <summary>
		/// Turns the back layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void B(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the back layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Bi(bool isAddToMoves = true);

		/// <summary>
		/// Turns the back layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void B2(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the front layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void F(bool isAddToMoves = true);

		/// <summary>
		/// Turns the front layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Fi(bool isAddToMoves = true);

		/// <summary>
		/// Turns the front layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void F2(bool isAddToMoves = true);

		/// <summary>
		/// Turns the bottom layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void D(bool isAddToMoves = true);

		/// <summary>
		/// Turns the bottom layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Di(bool isAddToMoves = true);

		/// <summary>
		/// Turns the bottom layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void D2(bool isAddToMoves = true);
		
		/// <summary>
		/// Changes the referential of the cube
		/// </summary>
		/// <param name="color">The middle piece color which will be placed on top layer</param>
		void changeReferential(RubikColor color);	

		/// <summary>
		/// Changes the refential of the cube: 
		/// Top layer becomes front layer,
		/// Front layer becomes bottom layer,
		/// Bottom Layer becomes back layer,
		/// Back layer becomes top layer,
		/// Right layer and Left layer remain the same.
		/// </summary>
		void turnCubeUp();

		/// <summary>
		/// Changes the referential of the cube: 
		/// Top layer becomes left layer,
		/// Left layer becomes bottom layer,
		/// Bottom layer becomes right layer,
		/// Right layer becomes top layer, 
		/// Front and back layers remain the same.
		/// </summary>
		void turnCubeRight();

		/// <summary>
		/// Changes the refential of the cube: 
		/// Top layer becomes back layer,
		/// Front layer becomes top layer,
		/// Bottom Layer becomes front layer,
		/// Back layer becomes bottom layer,
		/// Right layer and Left layer remain the same.
		/// </summary>
		void turnCubeDown();


		/// <summary>
		/// Changes the refential of the cube: 
		/// Top layer becomes right layer,
		/// Right layer becomes bottom layer,
		/// Bottom layer becomes left layer,
		/// Left layer becomes top layer,
		/// Front and back layers remain the same
		/// </summary>
		void turnCubeLeft();

		/// <summary>
		/// Resolves the cube to have a layer with the specified colors, using HumanSolver class method
		/// </summary>
		/// <param name="colors">The colors.</param>
		void resolve(RubikColor colors[]);

		/// <summary>
		/// Resolves the cube to have a layer with the specified colors, using RobotSolver class method
		/// </summary>
		/// <param name="colors">The expected colors</param>
		/// <param name="pRobot">The robot used to compute the cost of each move</param>
		void resolve(RubikColor colors[], Robot * pRobot);

		/// <summary>
		/// Prints the error to the console
		/// </summary>
		/// <param name="str">The string.</param>
		void error(std::string str);

		/// <summary>
		/// Checks each move to find moves that can be simplified. Normally, this method is not needed since the addMove method optimises before adding the move to the list
		/// </summary>
		void optimise();	

		/// <summary>
		/// Translates the "string" moves to actual corresponding functions (eg. "R" calls the function this-&gt;R())
		/// </summary>
		/// <param name="arrayOfMoves">The array of moves.</param>
		void applyMoves(std::vector<std::string>& arrayOfMoves);

		/// <summary>
		/// Translates the "string" move to actual corresponding function (eg. "R" calls the function this-&gt;R())
		/// </summary>
		/// <param name="move">The move.</param>
		void applyMove(std::string move);

		/// <summary>
		/// Gets the moves applied to this cube
		/// </summary>
		/// <returns></returns>
		std::vector<std::string> getMoves() { return moves; }		

		/// <summary>
		/// Sets the edge as locked, meaning it's in the correct position on the cube and should not be moved anymore
		/// </summary>
		/// <param name="index">The index.</param>
		/// <param name="value">if set to <c>true</c> [value].</param>
		void setLockedEdge(int index, bool value);

		/// <summary>
		/// Sets the corner as locked, meaning it's in the correct position on the cube and should not be moved anymore
		/// </summary>
		/// <param name="index">The index.</param>
		/// <param name="value">if set to <c>true</c> [value].</param>
		void setLockedCorner(int index, bool value);
		
		/// <summary>
		/// Gets the corner at corresponding index
		/// </summary>
		/// <param name="index">The index.</param>
		/// <returns>The corresponding corner</returns>
		CornerFace * getCorner(int index);
		
		/// <summary>
		/// Gets the edge at corresponding index
		/// </summary>
		/// <param name="index">The index.</param>
		/// <returns>The corresponding edge</returns>
		EdgeFace * getEdge(int index);
		
		/// <summary>
		/// Gets the middle face at corresponding index
		/// </summary>
		/// <param name="index">The index.</param>
		/// <returns>
		/// The corresponding middle face
		/// </returns>
		MiddleFace * getMiddle(int index);
		
		/// <summary>
		/// Gets the move at correspond index in the <c>moves</c> array
		/// </summary>
		/// <param name="">The index</param>
		/// <returns>
		/// The corresponding move
		/// </returns>
		std::string getMoveAtIndex(int);
		
		/// <summary>
		/// Gets the number of moves in the <c>moves</c> array
		/// </summary>
		/// <returns>The number of moves in the <c>moves</c> array</returns>
		int getNbMoves();

	private:
		//Static array giving the # used to represent the cube
		static int lines[9][12];

		//Gives the actual move in the changed referential
		std::map<std::string, std::string> movesDictionary;

		//Gives the function corresponding to a string (representing a rubik move)
		std::map<std::string, pfunc> movesFunctions;

		CornerFace * corners[24];
		EdgeFace * edges[24];
		MiddleFace * middle[8];

		//Array of moves
		std::vector<std::string> moves;
		
		/// <summary>
		/// Initializes the moves dictionary.
		/// </summary>
		void initMovesDictionaryAndFunctions();
		/// <summary>
		/// Initializes the corners and edges from the array given in the constructor
		/// </summary>
		/// <param name="arr">The arr.</param>
		void initCornersAndEdges(int arr[]);
		
		/// <summary>
		/// Initializes the corners and edges from the array given in the constructor
		/// </summary>
		/// <param name="arr">The arr.</param>
		void initCornersAndEdges(std::vector<std::vector<int>>& arr);

		/// <summary>
		/// Gives the offset used to read the indexes in the Rubik::lines static variable
		/// </summary>
		/// <param name="scannedLayerPosition">The layer index for the scanned cube array (std::vector<std::vector<int>>)</param>
		struct Offset getOffset(int scannedLayerPosition);
		
		/// <summary>
		/// Adds the move to the moves array. Will simplify the move according to the previous move in the array if possible.
		/// </summary>
		/// <param name="move">The move.</param>
		void addMove(std::string move);
		
		/// <summary>
		/// Finds the color corresponding to the # of the piece and adds the edge to the edges of the cube 
		/// </summary>
		/// <param name="position">The # of the piece</param>
		/// <param name="number">The actual position in the disordered cube</param>
		void addEdge(int position, int number);
		
		/// <summary>
		/// Finds the color corresponding to the # of the piece and adds the corner to the corners of the cube
		/// </summary>
		/// <param name="position">The position.</param>
		/// <param name="number">The number.</param>
		void addCorner(int position, int number);
		
		/// <summary>
		/// Finds the color corresponding to the # of the piece and adds the middle face to the middle faces of the cube
		/// </summary>
		/// <param name="position">The position.</param>
		/// <param name="number">The number.</param>
		void addMiddle(int position, int number);
		
		/// <summary>
		/// Add a corner with a certain color but without the corresponding # (will have to be computed later)
		/// </summary>
		/// <param name="index">The index.</param>
		/// <param name="color">The color.</param>
		void addCornerColor(int index, RubikColor color);

		/// <summary>
		/// Add an edge with a certain color but without the corresponding # (will have to be computed later)
		/// </summary>
		/// <param name="index">The index.</param>
		/// <param name="color">The color.</param>
		void addEdgeColor(int index, RubikColor color);

		/// <summary>
		/// Adds a middle face with a certain color but without the corresponding # (will have to be computed later)
		/// </summary>
		/// <param name="index">The index.</param>
		/// <param name="color">The color.</param>
		void addMiddleColor(int index, RubikColor color);

		/// <summary>
		/// Initializes the face numbers from colors.
		/// </summary>
		void initAllFacesNumbersFromColors();

		/// <summary>
		/// Initializes the edge numbers from colors.
		/// </summary>
		void initAllEdgesNumbersFromColors();


		/// <summary>
		/// Computes the edge piece numbers from colors.
		/// </summary>
		/// <param name="">The edge index (modulo 12)</param>
		void computeEdgePieceNumbersFromColors(int);


		/// <summary>
		/// Gets the possible edge numbers corresponding to the given color.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <returns>
		/// An array with the possible edge numbers
		/// </returns>
		std::vector<int> getPossibleEdgeNumbersFromColor(RubikColor color);

		/// <summary>
		/// Initializes all corners numbers from colors.
		/// </summary>
		void initAllCornersNumbersFromColors();
		
		/// <summary>
		/// Computes the corner piece number from colors.
		/// </summary>
		/// <param name="">The .</param>
		void computeCornerPieceNumberFromColors(int);
		
		/// <summary>
		/// Gets the possible corner numbers corresponding to the given color.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <returns>An array with the possible corner numbers</returns>
		std::vector<int> getPossibleCornerNumbersFromColor(RubikColor color);

		/// <summary>
		/// Shifts i1 --> i2 --> i3 --> i4 [--> i1
		/// </summary>
		/// <param name="array">The array.</param>
		/// <param name="i1">The i1.</param>
		/// <param name="i2">The i2.</param>
		/// <param name="i3">The i3.</param>
		/// <param name="i4">The i4.</param>
		void shift(Face * array[], int i1, int i2, int i3, int i4);
		
		/// <summary>
		/// Shifts i1 --> i2 --> i3 --> i4 [--> i1
		/// </summary>
		/// <param name="array">The array.</param>
		/// <param name="i1">The i1.</param>
		/// <param name="i2">The i2.</param>
		/// <param name="i3">The i3.</param>
		/// <param name="i4">The i4.</param>
		void shift(CornerFace * array[], int i1, int i2, int i3, int i4);
		
		/// <summary>
		/// Shifts i1 --> i2 --> i3 --> i4 [--> i1
		/// </summary>
		/// <param name="array">The array.</param>
		/// <param name="i1">The i1.</param>
		/// <param name="i2">The i2.</param>
		/// <param name="i3">The i3.</param>
		/// <param name="i4">The i4.</param>
		void shift(EdgeFace * array[], int i1, int i2, int i3, int i4);
		
		/// <summary>
		/// Shifts i1 --> i2 --> i3 --> i4 [--> i1
		/// </summary>
		/// <param name="array">The array.</param>
		/// <param name="i1">The i1.</param>
		/// <param name="i2">The i2.</param>
		/// <param name="i3">The i3.</param>
		/// <param name="i4">The i4.</param>
		void shift(MiddleFace * array[], int i1, int i2, int i3, int i4);
		
		/// <summary>
		/// Swaps i1 and i2 in the array
		/// </summary>
		/// <param name="array">The array.</param>
		/// <param name="i1">The i1.</param>
		/// <param name="i2">The i2.</param>
		void swap(Face * array[], int i1, int i2);

		/// <summary>
		/// When adding a move, shortens the current move with the previous move in the array (eg. 'R' and 'R' becomes 'R2')
		/// </summary>
		/// <param name="">The .</param>
		/// <returns></returns>
		int shortenMoves(int);
};

#endif