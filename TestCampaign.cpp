#include "TestCampaign.h"

TestCampaign::TestCampaign(int pieces[]) {
	for (int i = 0; i < 54; i++) {
		this->pieces[i] = pieces[i];
	}
}

TestCampaign::TestCampaign(std::vector<std::vector<int>>& rubikColors) {
	this->rubikColors = rubikColors;
	this->isRubikColors = true;
}

void TestCampaign::run() {
	Rubik::setVerbose(false);

	try {
		resolveTests();
	}
	catch (ResolutionException ex)
	{
		Rubik::setVerbose(true);
		solveOneCube(ex.getColors());
	}
}

void TestCampaign::time() {
	Rubik::setVerbose(false);
	try {
		resolveTimeTests();
	}
	catch (ResolutionException ex) {
		std::cout << "Failed" << std::endl;
		Rubik::setVerbose(true);
		solveOneCube(ex.getColors());
	}
}

void TestCampaign::resolveTimeTests() {
	Robot robot;
	this->passed = 0;
	std::clock_t start;
	double duration;

	start = std::clock();

	RubikColor rubikColors[6] = { RubikColor::WHITE, RubikColor::GREEN, RubikColor::RED, RubikColor::BLUE, RubikColor::ORANGE, RubikColor::YELLOW };
	RubikColor colors[9];

	for (int i1 = 0; i1 < 6; i1++) {
		colors[0] = rubikColors[i1];
		for (int i2 = 0; i2 < 6; i2++) {
			colors[1] = rubikColors[i2];
			for (int i3 = 0; i3 < 6; i3++) {
				colors[2] = rubikColors[i3];

				for (int i4 = 0; i4 < 6; i4++) {
					colors[3] = rubikColors[i4];

					for (int i6 = 0; i6 < 6; i6++) {
						colors[5] = rubikColors[i6];
						for (int i7 = 0; i7 < 6; i7++) {
							colors[6] = rubikColors[i7];

							std::cout << "RESULTS" << std::endl;
							std::cout << "Number of tests : " << this->passed << std::endl;
							if (this->passed > 0) std::cout << "Time per cube: " << ((std::clock() - start) / (double)CLOCKS_PER_SEC)/this->passed << std::endl;
							std::cout << std::endl;

							for (int i8 = 0; i8 < 6; i8++) {
								colors[7] = rubikColors[i8];
								for (int i9 = 0; i9 < 6; i9++) {
									colors[8] = rubikColors[i9];
									for (int i5 = 0; i5 < 6; i5++) {
										colors[4] = rubikColors[i5];

										time_resolveOneCube(colors, robot);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	std::cout << "RESULTS" << std::endl;
	std::cout << "Number of tests : " << this->passed << std::endl;
	if (this->passed > 0) std::cout << "Time per cube: " << ((std::clock() - start) / (double)CLOCKS_PER_SEC) / this->passed << std::endl;
	std::cout << std::endl;
	getchar();

}

void TestCampaign::time_resolveOneCube(RubikColor colors[], Robot& robot) {
	Rubik r = makeRubik();
	r.resolve(colors, &robot);
	this->passed++;
}

void TestCampaign::resolveTests() {
	this->failed = 0;
	this->passed = 0;
	this->nbMoves = 0;
	this->nbRobotMoves = 0;

	RubikColor rubikColors[6] = { RubikColor::WHITE, RubikColor::GREEN, RubikColor::RED, RubikColor::BLUE, RubikColor::ORANGE, RubikColor::YELLOW };
	RubikColor colors[9];

	for (int i1 = 0; i1 < 6; i1++) {
		colors[0] = rubikColors[i1];
		for (int i2 = 0; i2 < 6; i2++) {
			colors[1] = rubikColors[i2];
			for (int i3 = 0; i3 < 6; i3++) {
				colors[2] = rubikColors[i3];

				for (int i4 = 0; i4 < 6; i4++) {
					colors[3] = rubikColors[i4];

					for (int i6 = 0; i6 < 6; i6++) {
						colors[5] = rubikColors[i6];
						for (int i7 = 0; i7 < 6; i7++) {
							colors[6] = rubikColors[i7];

							std::cout << "RESULTS" << std::endl;
							std::cout << "Number of tests : " << this->passed + this->failed << std::endl;
							std::cout << "Passed : " << this->passed << std::endl;
							std::cout << "Failed : " << this->failed << std::endl;
							if (this->passed > 0) std::cout << "Average : " << this->nbMoves / (this->passed) << std::endl;
							if (this->passed > 0) std::cout << "Robot Average : " << this->nbRobotMoves / (this->passed) << std::endl;
							std::cout << std::endl;

							for (int i8 = 0; i8 < 6; i8++) {
								colors[7] = rubikColors[i8];
								for (int i9 = 0; i9 < 6; i9++) {
									colors[8] = rubikColors[i9];
									for (int i5 = 0; i5 < 6; i5++) {
										colors[4] = rubikColors[i5];

										resolveOneCube(colors);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	std::cout << "RESULTS (END)" << std::endl;
	std::cout << "Number of tests : " << this->passed + this->failed << std::endl;
	std::cout << "Passed : " << this->passed << std::endl;
	std::cout << "Failed : " << this->failed << std::endl;
	getchar();

}

std::vector<std::vector<int>> TestCampaign::copyRubikColors() {
	std::vector<std::vector<int>> result;

	int size = this->rubikColors.size();
	for (int i = 0; i < size; i++) {
		int size2 = this->rubikColors[i].size();
		std::vector<int> line;
		for (int j = 0; j < size2; j++) {
			line.push_back(this->rubikColors[i][j]);
		}
		result.push_back(line);
	}
	return result;
}

Rubik TestCampaign::makeRubik() {
	if (this->isRubikColors) {
		return Rubik(this->rubikColors);
	}
	return Rubik(this->pieces);
}

void TestCampaign::resolveOneCube(RubikColor colors[]) {
	Robot robot;

	Rubik rubik = makeRubik();
	rubik.resolve(colors, &robot);

	/*Rubik rubik2 = makeRubik();

	std::vector<std::string> moves = rubik.getMoves();
	rubik2.applyMoves(moves);

	rubik2.changeReferential(colors[4]);*/

	if (rubik/*2*/.verifyRubikColors(colors))
	{
		this->passed++;
		this->nbMoves += rubik.getMoves().size();
		robot.sendRubikMoves(/*moves*/rubik.getMoves());
		this->nbRobotMoves += robot.getRobotMoves().size();
	}
	else {
		this->failed++;
		std::cout << setcolor(RubikColor::RED) << "FAILED" << setcolor(RubikColor::WHITE) << "(passed " << this->passed << ", failed " << this->failed << ")" << std::endl;
		std::cout << "Expected colors :" << std::endl;
		for (int i = 0; i < 9; i++) {
			std::cout << setcolor(colors[i]) << "#";
			if (i % 3 == 2) {
				std::cout << std::endl;
			}
		}

		std::cout << setcolor(RubikColor::WHITE) << std::endl;
		std::cout << "Moves :";
		std::vector<std::string> moves = rubik.getMoves();
		int size = moves.size();
		for (int i = 0; i < size; i++) {
			std::cout << " " << moves[i];
		}
		std::cout << std::endl;

		std::cout << setcolor(RubikColor::WHITE) << "---------------------------------------------" << std::endl;
		std::cout << "Rubik2:" << std::endl;
		rubik/*2*/.printCube();
		throw ResolutionException("Incorrect resolution", colors);
	}
}

void TestCampaign::solveOneCube(RubikColor colors[]) {
	/* The numbers are specified this way

				01 02 03
				04 05 06
				07 08 09

	10 11 12	13 14 15   16 17 18   19 20 21
	22 23 24	25 26 27   28 29 30   31 32 33
	34 35 36	37 38 39   40 41 42   43 44 45

				46 47 48
				49 50 51
				52 53 54

	*/
	Robot robot;

	Rubik rubik = makeRubik();

	/*The colors are specified this way :
			1 2 3
			4 5 6
			7 8 9
	*/

	rubik.resolve(colors, &robot);


	std::cout << "Expected colors :" << std::endl;
	for (int i = 0; i < 9; i++) {
		std::cout << setcolor(colors[i]) << "#";
		if (i % 3 == 2) {
			std::cout << std::endl;
		}
	}

	std::cout << setcolor(RubikColor::WHITE) << std::endl;
	std::cout << "Moves :";
	std::vector<std::string> moves = rubik.getMoves();
	int size = moves.size();
	for (int i = 0; i < size; i++) {
		std::cout << " " << moves[i];
	}
	std::cout << std::endl;

	std::cout << setcolor(RubikColor::WHITE) << std::endl;

	robot.sendRubikMoves(rubik.getMoves());
	std::cout << "Robot Moves :";
	std::vector<std::string> rmoves = robot.getRobotMoves();
	size = rmoves.size();
	for (int i = 0; i < size; i++) {
		std::cout << " " << rmoves[i];
	}
	std::cout << std::endl;

	robot.printSentRobotMoves();


	std::cout << setcolor(RubikColor::WHITE) << "---------------------------------------------" << std::endl;
	rubik.printCube();
	getchar();
}