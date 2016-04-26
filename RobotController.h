#ifndef RUBIKROBOT_HEADER
#define RUBIKROBOT_HEADER	

#include <string>
#include <iostream>
#include <windows.h>
#include <commctrl.h>
#include <stdlib.h>

/// <summary>
/// Handles the communication with the Arduino card and therefore with the Robot's motors
/// </summary>
class RobotController {
private:	
	/// <summary>
	/// The port's name
	/// </summary>
	std::string port;	
	HANDLE hComm;

	/// <summary>
	/// Sends the s byte.
	/// </summary>
	/// <param name="">The char to send</param>
	/// <returns>If the robot receive the message or not</returns>
	bool sendSByte(unsigned char);

	/// <summary>
	/// Reads the s byte.
	/// </summary>
	/// <returns>The read char</returns>
	unsigned char readSByte();
	
	/// <summary>
	/// Opens the port to communicate with Arduino
	/// </summary>
	/// <returns>If the port has been opened or not</returns>
	bool openPort();
	
	/// <summary>
	/// Closes the port with Arduino
	/// </summary>
	/// <returns>If the port has been closed or not</returns>
	bool closePort();
	
	/// <summary>
	/// Setups the port.
	/// </summary>
	/// <returns>If the port has been setup or not</returns>
	bool setupPort();

public:		
	static bool RobotController::debug;
	/// <summary>
	/// Initializes a new instance of the <see cref="RobotController"/> class.
	/// </summary>
	/// <param name="port">The port used to communicate with Arduino</param>
	RobotController(std::string port = "COM3");

	/// <summary>
	/// Sends the specified char
	/// </summary>
	/// <param name="">The char to send</param>
	/// <returns>If the specified char has been received by the robot</returns>
	bool send(unsigned char);


	/// <summary>
	/// Waits until Arduino sends a char to read
	/// </summary>
	/// <returns>The read char</returns>
	unsigned char read();
	
	/// <summary>
	/// Initializes the port.
	/// </summary>
	/// <returns>If the port has been initialized or not</returns>
	bool initPort();
	
	/// <summary>
	/// Sets the port.
	/// </summary>
	/// <param name="">The name of the port</param>
	void setPort(std::string);
	
	/// <summary>
	/// Gets the port.
	/// </summary>
	/// <returns>The name of the port</returns>
	std::string getPort();

};

#endif
