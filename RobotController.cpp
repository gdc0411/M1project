#include "RobotController.h"

/// <summary>
/// The boolean debug mode
/// </summary>
bool RobotController::debug = false;

RobotController::RobotController(std::string port){
	this->port = port;
	this->initPort();
}

bool RobotController::send(unsigned char msg){
	this->sendSByte(msg);
	if (this->read() == msg){
		return true;
	}
	else {
		return false;
	}
}

unsigned char RobotController::read(){
	return this->readSByte();
}

bool RobotController::initPort(){
	if (openPort() && setupPort()) {
		if (RobotController::debug) std::cout << "Port open and configure" << std::endl;
		return true;
	}
	else {
		if (RobotController::debug) std::cout << "Error when opening and setting port" << std::endl;
		return false;
	}
}

void RobotController::setPort(std::string port){
	this->port = port;
}

std::string RobotController::getPort(){
	return this->port;
}

bool RobotController::sendSByte(unsigned char msg){
	DWORD dwWritten;
	if (WriteFile(hComm, &msg, sizeof(msg), &dwWritten, 0)) {
		if (RobotController::debug) std::cout << "wrote byte " << msg << " to serial port" << std::endl;
		return true;
	}
	else {
		if (RobotController::debug) std::cout << "serial port write failed" << std::endl;
		return false;
	}
}

unsigned char RobotController::readSByte(){
	DWORD dwRead;
	unsigned char lpBuf;

	ReadFile(hComm,				// handle of file to read
		&lpBuf,					// address of buffer that receives data
		sizeof(lpBuf),			// number of bytes to read
		&dwRead,					// address of number of bytes read
		0);						// address of structure for data
	if (RobotController::debug) std::cout << "Read byte " << lpBuf << " from serial port" << std::endl;
	return lpBuf;
}

bool RobotController::openPort(){
	if (RobotController::debug) std::cout << "-- Opening Port " << this->port << " --" << std::endl;

    //Convert multibyte string to wide-character string
    size_t sSize=strlen(this->port.c_str());
    wchar_t * dBuf=NULL;
    int dSize=mbstowcs(dBuf, this->port.c_str(), 0)+1;
    dBuf=new wchar_t[dSize];
    wmemset(dBuf, 0, dSize);
    int nRet=mbstowcs(dBuf, this->port.c_str(), sSize);
    if(nRet<=0)
    {
        printf("Failure to translate\n");
    }

    hComm = CreateFile(dBuf,					// pointer to name of the file
		GENERIC_READ | GENERIC_WRITE,	// access (read-write) mode 
		0,								// share mode 
		0,								// pointer to security attributes 
		OPEN_EXISTING,					// how to create
		0,								// file attributes
		0);							// handle to file with attributes to copy 


	if (hComm == INVALID_HANDLE_VALUE) {
		if (RobotController::debug) std::cout << "Failed to open serial port " << this->port << std::endl;
		return false;
	}
	else {
		if (RobotController::debug) std::cout << "Serial port " << this->port << " opened" << std::endl;
		return true;
	}
}

bool RobotController::closePort(){
	if (CloseHandle(hComm)) {
		if (RobotController::debug) std::cout << "Port closed" << std::endl;
		return true;
	}
	else {
		if (RobotController::debug) std::cout << "Port closed failed" << std::endl;
		return false;
	}
}

bool RobotController::setupPort(){
	DCB dcb;

	if (RobotController::debug) std::cout << "-- Getting DCB --" << std::endl;

	if (!GetCommState(hComm, &dcb)) {
		if (RobotController::debug) std::cout << "GetDCB failed" << std::endl;
		return false;
	}

	dcb.BaudRate = 9600;
	dcb.fParity = FALSE;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 8;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;

	if (RobotController::debug) std::cout << "DCB ready for use" << std::endl;
	if (!SetCommState(hComm, &dcb)) {
		if (RobotController::debug) std::cout << "Failed to set port state (" << GetLastError() << ")" << std::endl;
		return false;
	}
	else {
		if (RobotController::debug) std::cout << "Port setup complete" << std::endl;
		return true;
	}
}
