#ifndef ROBOT_H

#define ROBOT_H

#include "RobotState.h"
#include "RobotController.h"
#include "Face.h"
#include "Utils.h"
#include <string>
#include <vector>

#define NB_CAPTURE 6
#define ROBOT_DEBUG 1

/// <summary>
/// Class representing the robot
/// </summary>
class Robot {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Robot"/> class.
	/// </summary>
	Robot(int=0, cv::String = "Default Window Name");
	/// <summary>
	/// Converts and sends the rubik moves to the robot. Fills the robotMoves array
	/// </summary>
	/// <param name="rubikMoves">The rubik moves.</param>
	void sendRubikMoves(std::vector<std::string> rubikMoves);
	
	/// <summary>
	/// Gets the robot moves filled by the "sendRubikMoves" function
	/// </summary>
	/// <returns>The list of the robot moves</returns>
	std::vector<std::string> getRobotMoves() { return rmoves; };
	
	/// <summary>
	/// Computes the cost of a rubik move.
	/// </summary>
	/// <param name="rubikMoves">The rubik moves: New moves to send to the robot</param>
	/// <param name="previousRubikMove">The previous rubik move: Permits to determine the state of the robot before performing the new moves</param>
	/// <returns></returns>
	int getRubikMovesCost(std::vector<std::string> rubikMoves, std::string previousRubikMove);
	
	/// <summary>
	/// Gets the controller.
	/// </summary>
	/// <returns>The Robot Controller</returns>
	RobotController& getController();
	
	/// <summary>
	/// Determines if one cv::Rect intersect an another cv::Rect.
	/// </summary>
	/// <param name="">The list of contours delimited the cv::Rect</param>
	/// <returns>If one cv::Rect intersects an another cv::Rect</returns>
	bool isRectCollision(std::vector<SquareRubik>);
		
	/// <summary>
	/// Formats the structure in order to be formatted as the input of the algorithm.
	/// </summary>
	/// <param name="">The structure to be format</param>
	/// <returns>The formatted list</returns>
	std::vector<std::vector<int>> formatToAlgorithm(std::vector<std::vector<SquareRubik>>);
	
	/// <summary>
	/// Swaps the specified side.
	/// </summary>
	/// <param name="">The side to be swap</param>
	/// <param name="">The ordered indexes</param>
	/// <returns></returns>
	std::vector<SquareRubik> Robot::swap(std::vector<SquareRubik>, std::vector<int>);
		
	/// <summary>
	/// Formats the sides.
	/// </summary>
	/// <param name="sides">The sides.</param>
	/// <returns>The formatted sides</returns>
	std::vector<std::vector<SquareRubik>> formatSides(std::vector<std::vector<SquareRubik>>);

	/// <summary>
	/// Launches the capture with OpenCV and the camera
	/// </summary>
	/// <returns>The representation of the Rubik's Cube which is in the robot</returns>
	std::vector<std::vector<int>> launchCapture();
	
	/// <summary>
	/// Sets the camera identifier.
	/// </summary>
	/// <param name="camera_id">The camera id</param>
	void setCameraId(int);
	
	/// <summary>
	/// Gets the camera identifier.
	/// </summary>
	/// <returns>The camera id</returns>
	int getCameraId();
	
	/// <summary>
	/// Sets the square count.
	/// </summary>
	/// <param name="">The number of square found on a single side</param>
	void setSquareCount(int);
	
	/// <summary>
	/// Gets the square count.
	/// </summary>
	/// <returns>The number of square found on a single side</returns>
	int getSquareCount();
	
	/// <summary>
	/// Sets the name of the window.
	/// </summary>
	/// <param name="">The name of the window</param>
	void setWindowName(cv::String);
	
	/// <summary>
	/// Gets the name of the window.
	/// </summary>
	/// <returns>The name of the window</returns>
	cv::String getWindowName();
	
	/// <summary>
	/// Sets the robot position.
	/// </summary>
	/// <param name="">The position in which the robot has to be to take a picture of the Rubik's cube</param>
	/// <returns></returns>
	bool setRobotPosition(int);
		
	/// <summary>
	/// Sorts the result.
	/// </summary>
	/// <param name="">The list of each square on a single side</param>
	/// <returns>The list of each square sorted with this pattern :
	///								012
	///								345
	///								678 </returns>
	std::vector<SquareRubik> sortResult(std::vector<SquareRubik>);
	
	/// <summary>
	/// Sorts the x axis.
	/// </summary>
	/// <param name="r1">The first SquareRubik</param>
	/// <param name="r2">The second SquareRubik</param>
	/// <returns>If the x position of r2 is greater than the one of r1</returns>
	static bool sortXAxis(SquareRubik r1, SquareRubik r2) { return r1.position.x < r2.position.x; };
	
	/// <summary>
	/// Sorts the y axis.
	/// </summary>
	/// <param name="r1">The first SquareRubik</param>
	/// <param name="r2">The second SquareRubik</param>
	/// <returns>If the y position of r2 is greater than the one of r1</returns>
	static bool sortYAxis(SquareRubik r1, SquareRubik r2) { return r1.position.y < r2.position.y; };

private:	
	/// <summary>
	/// The state of the robot
	/// </summary>
	RobotState state;	
	/// <summary>
	/// Handles the communication with the Arduino card and therefore with the Robot's motors
	/// </summary>
	RobotController controller;

	/// <summary>
	/// Converts rubik move and sends the associated robot moves
	/// </summary>
	/// <param name="rubikMove">The rubik move.</param>
	void addMove(std::string rubikMove);
	
	/// <summary>
	/// Put the rubik's cube down
	/// </summary>
	void endMove();
	
	/// <summary>
	/// The robot moves
	/// </summary>
	std::vector<std::string> rmoves;
	
	/// <summary>
	/// Turn the top motor from 180° to 90°
	/// </summary>
	bool U0_to_1();

	/// <summary>
	/// Turn the top motor from 180° to 0°
	/// </summary>
	bool U0_to_2();

	/// <summary>
	/// Turn the top motor from 90° to 0°
	/// </summary>
	bool U1_to_0();

	/// <summary>
	/// Turn the top motor from 90° to 0°
	/// </summary>
	bool U1_to_2();

	/// <summary>
	/// Turn the top motor from 0° to 180°
	/// </summary>
	bool U2_to_0();

	/// <summary>
	/// Turn the top motor from 0° to 180°
	/// </summary>
	bool U2_to_1();

	/// <summary>
	/// Turns the top motor to 180°
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool U0();
	
	/// <summary>
	/// Turns the top motor to 90°
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool U1();
	
	/// <summary>
	/// Turns the top motor to 0°
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool U2();
	
	/// <summary>
	/// Adds 90° to the motor position
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool U();
	
	/// <summary>
	/// Removes 90° from the motor position
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool Ui();
	
	/// <summary>
	/// Goes up from height 0 to height 1
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H0_to_1();
	
	/// <summary>
	/// Goes up from height 0 to height 2
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H0_to_2();
	
	/// <summary>
	/// Goes up from height 0 to height 3
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H0_to_3();
	
	/// <summary>
	/// Goes up from height 1 to height 2
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H1_to_2();
	
	/// <summary>
	/// Goes up from height 1 to height 3
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H1_to_3();
	
	/// <summary>
	/// Goes up from height 2 to height 3
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H2_to_3();
	
	/// <summary>
	/// Goes down from height 3 to height 0
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D3_to_0();
	
	/// <summary>
	/// Goes down from height 2 to height 0
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D2_to_0();
	
	/// <summary>
	/// Goes down from height 1 to height 0
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D1_to_0();
	
	/// <summary>
	/// Goes down from height 2 to height 1
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D2_to_1();
	
	/// <summary>
	/// Goes down from height 3 to height 2
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D3_to_2();
	
	/// <summary>
	/// Goes down from height 3 to height 1
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D3_to_1();
	
	/// <summary>
	/// Goes up one level
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H1();
	
	/// <summary> Goes up two levels
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H2();
	
	/// <summary> Goes up three levels
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool H3();
	
	/// <summary> Goes down one level
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D1();
	
	/// <summary> Goes down two levels
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D2();
	
	/// <summary> Goes down three levels
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool D3();


	/// <summary>
	/// Put the cube in reversed position
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool Bi();

	/// <summary>
	/// Put the cube in non-reversed position
	/// </summary>
	/// <returns>If the move has succeeded or not</returns>
	bool B();

	/// <summary>
	/// Resets the height position (goes back to height 0)
	/// </summary>
	void resetHeight();

	/// <summary>
	/// Goes up or down, according to the height value specified (positive or negative value)
	/// </summary>
	/// <param name="height">The height to go up</param>
	void addHeight(int);

	/// <summary>
	/// Goes down according to the height value specified
	/// </summary>
	/// <param name="height">How low to go</param>
	void goDown(int);

	/// <summary>
	/// Goes up according to the height value specified
	/// </summary>
	/// <param name="height">How high to go</param>
	void goUp(int);

	/// <summary>
	/// Rotates <c>value</c> times
	/// </summary>
	/// <param name="nbRotations">The number of rotations to make (positive = clockwise, negative = counterclockwise)</param>
	void rotate(int);
	
	/// <summary>
	/// Sends the message and waits for the robot to send a message, reads it and checks if it corresponds to the sent message
	/// </summary>
	/// <param name="">The message</param>
	/// <returns>true if the read message from the robot is the same as the one sent</returns>
	bool sendMessageAndRead(std::string);
	
	/// <summary>
	/// The id of the camera
	/// </summary>
	int camera_id;
	
	/// <summary>
	/// The number of square found on a single side
	/// </summary>
	int square_count;
	
	/// <summary>
	/// Filter the frame to only detect squares we need
	/// </summary>
	/// <param name="rec">The square found by OpenCV</param>
	/// <returns>If the rectangle shape is part of the Rubik's cube</returns>
	bool filterRect(cv::Rect);
	
	/// <summary>
	/// The name of the camera window
	/// </summary>
	cv::String window_name;
	
	/// <summary>
	/// Defines the color text.
	/// </summary>
	/// <param name="colorid">The color id</param>
	/// <returns>The color letter to print</returns>
	cv::String defineColorText(int);
};

#endif