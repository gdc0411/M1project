#include "RobotState.h"

std::map<std::string, RobotState> RobotState::robotStates = initRobotStatesMap();

RobotState::RobotState(int height, bool balancier, int rotator, std::string referential) {
	this->balancer = balancier;
	this->height = height;
	this->referential = referential;
	this->rotator = rotator;
}

void RobotState::reset() {
	this->balancer = false;
	this->height = 0;
	this->referential = _U;
	this->rotator = 1;
}

std::map<std::string, RobotState> RobotState::initRobotStatesMap() {
	std::map<std::string, RobotState> map;
	map[_U] = RobotState(1, false, 1, _U);
	map[_Ui] = RobotState(1, false, -1, _U);
	map[_U2] = RobotState(1, false, 2, _U);
	map[_D] = RobotState(2, false, 1, _U);
	map[_Di] = RobotState(2, false, -1, _U);
	map[_D2] = RobotState(2, false, 2, _U);
	map[_F] = RobotState(1, true, 1, _F);
	map[_Fi] = RobotState(1, true, -1, _F);
	map[_F2] = RobotState(1, true, 2, _F);
	map[_B] = RobotState(2, true, 1, _F);
	map[_Bi] = RobotState(2, true, -1, _F);
	map[_B2] = RobotState(2, true, 2, _F);
	map[_R] = RobotState(1, true, 1, _R); //H3, U, D3, Ui, B, H1, U
	map[_Ri] = RobotState(1, true, -1, _R);
	map[_R2] = RobotState(1, true, 2, _R);
	map[_L] = RobotState(2, true, 1, _R);
	map[_Li] = RobotState(2, true, -1, _R);
	map[_L2] = RobotState(2, true, 2, _R);
	return map;
}

RobotState RobotState::getState(std::string rubikMove) {
	return RobotState::robotStates[rubikMove];
}
